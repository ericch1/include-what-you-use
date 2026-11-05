//===--- implementation_file_negative-i4.h - test input file for iwyu -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I4_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I4_H_

// IWYU: NegFwdThenDefined needs a declaration
inline int NegHelper(const NegFwdThenDefined& f) {
  // IWYU: NegFwdThenDefined is...*implementation_file_negative-i1.h
  return sizeof(f);
}

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I4_H_

/**** IWYU_SUMMARY

tests/cxx/implementation_file_negative-i4.h should add these lines:
#include "tests/cxx/implementation_file_negative-i1.h"

tests/cxx/implementation_file_negative-i4.h should remove these lines:

The full include-list for tests/cxx/implementation_file_negative-i4.h:
#include "tests/cxx/implementation_file_negative-i1.h"  // for NegFwdThenDefined

***** IWYU_SUMMARY */
