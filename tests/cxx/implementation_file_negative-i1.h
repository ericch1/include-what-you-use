//===--- implementation_file_negative-i1.h - test input file for iwyu -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I1_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I1_H_

class NegFwdThenDefined {};

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I1_H_

/**** IWYU_SUMMARY

(tests/cxx/implementation_file_negative-i1.h has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
