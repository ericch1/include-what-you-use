//===--- implementation_file_negative-i2.h - test input file for iwyu -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I2_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I2_H_

// A header of its own, which defines a function that -d1.h declares.
inline int NegLog(const char* message) {
  return message[0];
}

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_IMPLEMENTATION_FILE_NEGATIVE_I2_H_

/**** IWYU_SUMMARY

(tests/cxx/implementation_file_negative-i2.h has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
