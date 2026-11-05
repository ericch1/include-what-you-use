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
//            -Xiwyu --check_also=tests/cxx/implementation_file-d2.h \
//            -Xiwyu --check_also=tests/cxx/implementation_file-d1.inl

// Tests implementation files: implementation_file.h keeps its inline and
// template definitions in implementation_file-impl.icc, which it #includes
// itself, and which #includes implementation_file-detail.icc.  These files
// define what implementation_file.h declares, so:
// - implementation_file.h keeps its #include of
//   implementation_file-impl.icc, which itself keeps its #include of
//   implementation_file-detail.icc;
// - they may use what implementation_file.h #includes, without #including
//   it again, as long as implementation_file.h needs it too: the #include
//   of -i1.h moves to implementation_file-impl.icc, the only one using it;
// - users of what they define are told to #include implementation_file.h.
//
// The same holds for the implementation files of other headers:
// - implementation_file-d1.inl is analyzed, but not its header: it doesn't
//   inherit from it, so it #includes indirect.h itself;
// - implementation_file-d2.h defines its class in a namespace, in two files
//   that implementation_file-d2-all.icc #includes, and nothing else does;
// - implementation_file-d3.inl has a pragma, which wins: its users are
//   told to #include implementation_file-d3-api.h.

// Makes clang look up implementation_file-impl.icc before
// implementation_file.h: implementation_file.h must still be analyzed
// first.
#if __has_include("tests/cxx/implementation_file-impl.icc")
#endif

#include "tests/cxx/implementation_file-d1.h"
#include "tests/cxx/implementation_file-d2.h"
#include "tests/cxx/implementation_file-d3-api.h"
#include "tests/cxx/implementation_file.h"

void Use() {
  ImplFileClass c;
  c.InlineMethod();
  c.DetailMethod();
  c.TemplateMethod(1);
  ImplFileFunction(1);
  ImplFileTemplate(1);

  ImplFileD1Class d1;
  d1.InlineMethod();

  impl_file::D2Class d2;
  d2.A();
  d2.B();

  ImplFileD3Compute(1);
}

/**** IWYU_SUMMARY

(tests/cxx/implementation_file.cc has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
