//===--- implementation_file-d3.inl - test input file for iwyu ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU pragma: private, include "tests/cxx/implementation_file-d3-api.h"

inline int ImplFileD3Compute(int i) {
  return 3 * i;
}
