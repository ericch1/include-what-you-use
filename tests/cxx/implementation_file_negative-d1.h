//===--- implementation_file_negative-d1.h - test input file for iwyu -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_D1_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_D1_H_

// Forward declarations, then the headers with the definitions.
class NegFwdThenDefined;
int NegLog(const char* message);
#include "tests/cxx/implementation_file_negative-i1.h"
#include "tests/cxx/implementation_file_negative-i2.h"

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_D1_H_
