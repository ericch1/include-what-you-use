//===--- implementation_file-d1.inl - test input file for iwyu ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Analyzed without its header, so it gets no #include from it.

inline int ImplFileD1Class::InlineMethod() {
  // IWYU: IndirectClass is...*indirect.h
  IndirectClass local;
  // IWYU: IndirectClass is...*indirect.h
  return local.a;
}

/**** IWYU_SUMMARY

tests/cxx/implementation_file-d1.inl should add these lines:
#include "tests/cxx/indirect.h"

tests/cxx/implementation_file-d1.inl should remove these lines:

The full include-list for tests/cxx/implementation_file-d1.inl:
#include "tests/cxx/indirect.h"  // for IndirectClass

***** IWYU_SUMMARY */
