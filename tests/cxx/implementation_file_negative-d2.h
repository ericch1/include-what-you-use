//===--- implementation_file_negative-d2.h - test input file for iwyu -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_D2_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_D2_H_

// Needs -i3.h for both functions: a friend declaration only makes
// NegCompute a friend, and the declaration of NegOther comes too late.
class NegWidget {
  friend int NegCompute();
};

#include "tests/cxx/implementation_file_negative-i3.h"

inline int NegTwice() {
  return NegCompute() + NegOther();
}

int NegOther();

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_D2_H_

/**** IWYU_SUMMARY

(tests/cxx/implementation_file_negative-d2.h has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
