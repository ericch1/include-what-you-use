#!/usr/bin/env python3

##===--- iwyu_test_util_test.py - test for iwyu_test_util.py --------------===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

"""Tests for the IWYU test harness itself.

The harness decides which files an IWYU test checks; when it gets that wrong,
tests fail for reasons that have nothing to do with IWYU, or pass while
checking nothing.  These tests pin down that decision without running IWYU.
"""

import os
import shutil
import tempfile
import unittest

import iwyu_test_util


class CollectFilesToCheckTest(unittest.TestCase):
  """Tests _CollectFilesToCheck()."""

  def setUp(self):
    self.olddir = os.getcwd()
    self.tempdir = tempfile.mkdtemp()
    os.chdir(self.tempdir)

  def tearDown(self):
    os.chdir(self.olddir)
    shutil.rmtree(self.tempdir)

  def _MakeFile(self, filename, contents='// test input\n'):
    with open(filename, 'w') as fileobj:
      fileobj.write(contents)
    return filename

  def _MakeTestFile(self, filename='foo.cc', iwyu_args=None):
    contents = ''
    if iwyu_args:
      contents = '// IWYU_ARGS: %s\n' % iwyu_args
    return self._MakeFile(filename, contents)

  def _Collect(self, cpp_files_to_check, actual_summaries, cc_file=None):
    return iwyu_test_util._CollectFilesToCheck(
        cc_file or self._MakeTestFile(), cpp_files_to_check, actual_summaries)

  def _MakeFileWithSummary(self, filename):
    return self._MakeFile(filename,
                          '/**** IWYU_SUMMARY\n'
                          '\n'
                          '(%s has correct #includes/fwd-decls)\n'
                          '\n'
                          '***** IWYU_SUMMARY */\n' % filename)

  def testKeepsTheCallersFilesInOrder(self):
    """The caller's candidates are checked even without a summary."""
    files = self._Collect(['foo.cc', 'foo.h'], {})
    self.assertEqual(['foo.cc', 'foo.h'], files)

  def testAddsReportedFileTheCallerDidNotList(self):
    """A --check_also target outside the test's globs is still checked."""
    self._MakeFile('foo.inc')
    files = self._Collect(['foo.cc'], {'foo.cc': [], 'foo.inc': []})
    self.assertEqual(['foo.cc', 'foo.inc'], files)

  def testDoesNotListACallersFileTwice(self):
    self._MakeFile('foo.h')
    files = self._Collect(['foo.cc', 'foo.h'], {'foo.cc': [], 'foo.h': []})
    self.assertEqual(['foo.cc', 'foo.h'], files)

  def testSkipsFilesOutsideTheTestTree(self):
    """Library headers are reported on too, and carry no expectations."""
    files = self._Collect(
        ['foo.cc'], {'foo.cc': [], os.path.join(os.sep, 'usr', 'include',
                                                'stdio.h'): []})
    self.assertEqual(['foo.cc'], files)

  def testSkipsPathsThatDoNotResolve(self):
    """A reported path need not name a file we can open."""
    files = self._Collect(['foo.cc'], {'foo.cc': [], 'nonexistent.h': []})
    self.assertEqual(['foo.cc'], files)

  def testAddsReportedFilesInSortedOrder(self):
    self._MakeFile('b.inc')
    self._MakeFile('a.inc')
    files = self._Collect(['foo.cc'], {'b.inc': [], 'a.inc': []})
    self.assertEqual(['foo.cc', 'a.inc', 'b.inc'], files)

  def testReadsExpectationsFromAReportedFile(self):
    """End to end: the collected files are the ones expectations come from."""
    self._MakeFile('foo.cc')
    with open('foo.inc', 'w') as fileobj:
      fileobj.write('/**** IWYU_SUMMARY\n'
                    '\n'
                    '(foo.inc has correct #includes/fwd-decls)\n'
                    '\n'
                    '***** IWYU_SUMMARY */\n')
    files = self._Collect(['foo.cc'], {'foo.inc': []})
    self.assertEqual(
        {'foo.inc': ['(foo.inc has correct #includes/fwd-decls)\n']},
        iwyu_test_util._GetExpectedSummaries(files))


  def testAddsCheckAlsoTargetsThatWereNotReportedOn(self):
    """A --check_also target with an IWYU_SUMMARY must be checked, so that a
    summary IWYU stopped emitting is noticed."""
    self._MakeFileWithSummary('foo.inc')
    cc_file = self._MakeTestFile(
        iwyu_args='-Xiwyu --check_also=foo.inc -I .')
    files = self._Collect(['foo.cc'], {}, cc_file=cc_file)
    self.assertEqual(['foo.cc', 'foo.inc'], files)

  def testIgnoresCheckAlsoPatterns(self):
    """A pattern says nothing about what should be reported: IWYU reports on a
    --check_also file only if the translation unit includes it, and a pattern
    matches headers belonging to other tests too."""
    self._MakeFileWithSummary('foo-d1.h')
    self._MakeFileWithSummary('other-d1.h')
    cc_file = self._MakeTestFile(iwyu_args='-Xiwyu --check_also="*-d1.h"')
    files = self._Collect(['foo.cc'], {}, cc_file=cc_file)
    self.assertEqual(['foo.cc'], files)

  def testIgnoresCheckAlsoTargetsWithAnEmptySummary(self):
    self._MakeFile('foo.inc',
                   '/**** IWYU_SUMMARY\n\n***** IWYU_SUMMARY */\n')
    cc_file = self._MakeTestFile(iwyu_args='-Xiwyu --check_also=foo.inc')
    files = self._Collect(['foo.cc'], {}, cc_file=cc_file)
    self.assertEqual(['foo.cc'], files)

  def testIgnoresCheckAlsoTargetsWithoutASummary(self):
    """Without an IWYU_SUMMARY there is nothing to miss; whatever IWYU says
    about such a file is checked through the summary output alone."""
    self._MakeFile('foo.inc')
    cc_file = self._MakeTestFile(iwyu_args='-Xiwyu --check_also=foo.inc')
    files = self._Collect(['foo.cc'], {}, cc_file=cc_file)
    self.assertEqual(['foo.cc'], files)

  def testIgnoresCheckAlsoTargetsThatDoNotResolveHere(self):
    """IWYU also matches --check_also against include directories."""
    cc_file = self._MakeTestFile(
        iwyu_args='-Xiwyu --check_also=elsewhere/foo.h')
    files = self._Collect(['foo.cc'], {}, cc_file=cc_file)
    self.assertEqual(['foo.cc'], files)

  def testDoesNotListACheckAlsoTargetTwice(self):
    self._MakeFileWithSummary('foo.inc')
    cc_file = self._MakeTestFile(iwyu_args='-Xiwyu --check_also=foo.inc')
    files = self._Collect(['foo.cc'], {'foo.inc': []}, cc_file=cc_file)
    self.assertEqual(['foo.cc', 'foo.inc'], files)


class CompareExpectedAndActualSummariesTest(unittest.TestCase):
  """Tests _CompareExpectedAndActualSummaries()."""

  def testMatchingSummariesDoNotFail(self):
    summary = {'foo.h': ['(foo.h has correct #includes/fwd-decls)\n']}
    self.assertEqual([], iwyu_test_util._CompareExpectedAndActualSummaries(
        summary, dict(summary)))

  def testDifferingSummariesAreDiffed(self):
    failures = iwyu_test_util._CompareExpectedAndActualSummaries(
        {'foo.h': ['#include "bar.h"\n']}, {'foo.h': ['#include "baz.h"\n']})
    self.assertIn('Unexpected summary diffs for foo.h', ''.join(failures))

  def testUnexpectedSummaryIsReported(self):
    """IWYU reported on a file that expects nothing."""
    failures = iwyu_test_util._CompareExpectedAndActualSummaries(
        {}, {'foo.h': ['#include "bar.h"\n']})
    self.assertIn('Unexpected summary diffs for foo.h', ''.join(failures))

  def testAnEmptyExpectedSummaryExpectsNoSummary(self):
    """The driver tests spell out an empty IWYU_SUMMARY to say that IWYU
    should report nothing at all."""
    self.assertEqual([], iwyu_test_util._CompareExpectedAndActualSummaries(
        {'foo.c': []}, {}))

  def testMissingSummaryIsReportedInItsOwnRight(self):
    """The file carries an IWYU_SUMMARY, but IWYU never checked it."""
    failures = iwyu_test_util._CompareExpectedAndActualSummaries(
        {'foo.h': ['#include "bar.h"\n']}, {})
    self.assertIn('No summary reported for foo.h', ''.join(failures))


class GetActualSummariesTest(unittest.TestCase):
  """Tests that _GetActualSummaries() names the files _CollectFilesToCheck()
  keys on."""

  def testExtractsFileNamesFromIwyuOutput(self):
    output = """\

tests/cxx/foo.cc should add these lines:
#include "tests/cxx/bar.h"

tests/cxx/foo.cc should remove these lines:

The full include-list for tests/cxx/foo.cc:
#include "tests/cxx/bar.h"  // for Bar
---
(tests/cxx/foo.inc has correct #includes/fwd-decls)
""".splitlines(True)
    self.assertEqual(['tests/cxx/foo.cc', 'tests/cxx/foo.inc'],
                     sorted(iwyu_test_util._GetActualSummaries(output)))


if __name__ == '__main__':
  unittest.main()
