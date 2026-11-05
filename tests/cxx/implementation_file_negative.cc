//===--- implementation_file_negative.cc - test input file for iwyu -------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -I . \
//            -Xiwyu --check_also=tests/cxx/implementation_file_negative-i*.h \
//            -Xiwyu --check_also=tests/cxx/implementation_file_negative-d2.h

// Tests files that a header #includes, but that are not implementation
// files of that header, although they define something it declares.  If
// they were taken for implementation files, this file would be told to
// #include implementation_file_negative-d1.h instead of them.  Likewise,
// -i3.h is not an implementation file of -d2.h, which only declares what
// -i3.h defines in a friend declaration, or after using it.

#include "tests/cxx/implementation_file_negative-d1.h"
#include "tests/cxx/implementation_file_negative-d2.h"
#include "tests/cxx/implementation_file_negative-i2.h"

void Use() {
  // Defined in -i1.h, after a forward declaration in -d1.h.
  // IWYU: NegFwdThenDefined is...*implementation_file_negative-i1.h
  NegFwdThenDefined f;
  // Defined in -i2.h, declared in -d1.h.  This file #includes -i2.h too.
  NegLog("message");
  NegTwice();
  // Defined in -i3.h, which only -d2.h #includes.
  // IWYU: NegCompute() is...*implementation_file_negative-i3.h
  NegCompute();
  // IWYU: NegOther() is...*implementation_file_negative-i3.h
  NegOther();
}

/**** IWYU_SUMMARY

tests/cxx/implementation_file_negative.cc should add these lines:
#include "tests/cxx/implementation_file_negative-i1.h"
#include "tests/cxx/implementation_file_negative-i3.h"

tests/cxx/implementation_file_negative.cc should remove these lines:
- #include "tests/cxx/implementation_file_negative-d1.h"  // lines XX-XX

The full include-list for tests/cxx/implementation_file_negative.cc:
#include "tests/cxx/implementation_file_negative-d2.h"  // for NegTwice
#include "tests/cxx/implementation_file_negative-i1.h"  // for NegFwdThenDefined
#include "tests/cxx/implementation_file_negative-i2.h"  // for NegLog
#include "tests/cxx/implementation_file_negative-i3.h"  // for NegCompute, NegOther

***** IWYU_SUMMARY */
