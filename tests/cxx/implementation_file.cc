//===--- implementation_file.cc - test input file for iwyu ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -I . -Xiwyu --check_also=tests/cxx/implementation_file-d2.h

// Tests that IWYU detects implementation files, with no mapping or pragma.
// implementation_file.h keeps its inline definitions in
// implementation_file-impl.icc and #includes that file itself.  IWYU
// recognizes it because it defines what implementation_file.h declares.
// So it is analyzed with implementation_file.h, may use what that file
// #includes, and is private to it.
//
// The same holds for the implementation files of other headers.
// implementation_file-d1.h is not reported on, but users of what its
// implementation file defines are still told to #include it, not the
// implementation file.  implementation_file-d2.h is reported on thanks to
// --check_also, and so is its implementation file.

#include "tests/cxx/implementation_file-d1.h"
#include "tests/cxx/implementation_file-d2.h"
#include "tests/cxx/implementation_file.h"

void Use() {
  ImplFileClass c;
  c.InlineMethod();
  c.TemplateMethod(1);
  ImplFileFunction(1);
  ImplFileTemplate(1);

  ImplFileD1Class d1;
  d1.InlineMethod();

  ImplFileD2Class d2;
  d2.InlineMethod();
}

/**** IWYU_SUMMARY

(tests/cxx/implementation_file.cc has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
