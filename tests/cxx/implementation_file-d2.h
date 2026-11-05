//===--- implementation_file-d2.h - test input file for iwyu --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_D2_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_D2_H_

#include "tests/cxx/indirect.h"

namespace impl_file {

class D2Class {
 public:
  int A() const;
  int B() const;

 private:
  IndirectClass member;
};

}  // namespace impl_file

#include "tests/cxx/implementation_file-d2-all.icc"

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_D2_H_

/**** IWYU_SUMMARY

(tests/cxx/implementation_file-d2.h has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
