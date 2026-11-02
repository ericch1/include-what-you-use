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

#include "tests/cxx/implementation_file_negative-i3.h"
#include "tests/cxx/indirect.h"

// A forward declaration, then the header with the definition.
class NegFwdThenDefined;
#include "tests/cxx/implementation_file_negative-i1.h"

#include "tests/cxx/implementation_file_negative-i2.h"

enum NegColor {
#define NEG_COLOR(name) name,
#include "tests/cxx/implementation_file_negative-i4.def"
#undef NEG_COLOR
};

// Defined by a macro whose body is in -i3.h: the definition belongs here,
// where the macro is expanded.
int NegCreate();
NEG_DEFINE_CREATE()

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_D1_H_
