//===--- implementation_file.h - test input file for iwyu -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_H_

#include "tests/cxx/implementation_file-i1.h"
#include "tests/cxx/indirect.h"

class ImplFileClass {
 public:
  void InlineMethod();
  void DetailMethod();
  bool Equals(const ImplFileClass& other) const;
  template <typename T>
  void TemplateMethod(T t);

 private:
  IndirectClass member;
};

int ImplFileFunction(int i);

template <typename T>
T ImplFileTemplate(T t);

#include "implementation_file-impl.icc"

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_H_

/**** IWYU_SUMMARY

tests/cxx/implementation_file.h should add these lines:

tests/cxx/implementation_file.h should remove these lines:
- #include "tests/cxx/implementation_file-i1.h"  // lines XX-XX

The full include-list for tests/cxx/implementation_file.h:
#include "implementation_file-impl.icc"
#include "tests/cxx/indirect.h"  // for IndirectClass

***** IWYU_SUMMARY */
