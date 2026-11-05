//===--- implementation_file.cc - test input file for iwyu ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -I . \
//            -Xiwyu --check_also=tests/cxx/implementation_file-*.icc \
//            -Xiwyu --check_also=tests/cxx/implementation_file-d1.inl

// Tests implementation files: implementation_file.h keeps its inline and
// template definitions in implementation_file-detail.icc, which it
// #includes through implementation_file-impl.icc, and nothing else does.
// So:
// - implementation_file.h keeps its #include of implementation_file-impl.icc,
//   which keeps its #include of implementation_file-detail.icc;
// - implementation_file-detail.icc may use what implementation_file.h
//   #includes, without #including it again, as long as
//   implementation_file.h needs it too: the #include of -i1.h moves to
//   implementation_file-detail.icc, the only file using it;
// - users of what it defines are told to #include implementation_file.h.
//
// The same holds for the implementation files of other headers:
// - implementation_file-d1.inl is analyzed, but not its header: it doesn't
//   inherit from it, so it #includes indirect.h itself;
// - implementation_file-d3.inl has a pragma, which wins: its users are
//   told to #include implementation_file-d3-api.h.

// Makes clang look up implementation_file-impl.icc before
// implementation_file.h: implementation_file.h must still be analyzed
// first.
#if __has_include("tests/cxx/implementation_file-impl.icc")
#endif

#include "tests/cxx/implementation_file-d1.h"
#include "tests/cxx/implementation_file-d3-api.h"
#include "tests/cxx/implementation_file.h"

void Use() {
  impl_file::ImplFileClass c;
  c.InlineMethod();
  c.Equals(c);
  c.TemplateMethod(1);
  impl_file::ImplFileFunction(1);
  impl_file::ImplFileTemplate(1);

  ImplFileD1Class d1;
  d1.InlineMethod();

  ImplFileD3Compute(1);
}

/**** IWYU_SUMMARY

(tests/cxx/implementation_file.cc has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
