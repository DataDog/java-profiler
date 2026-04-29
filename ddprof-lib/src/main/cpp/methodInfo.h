/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _METHODINFO_H
#define _METHODINFO_H

#include <cassert>
#include <inttypes.h>
#include <jvmti.h>
#include <map>
#include <memory>

#include "arch.h"
#include "frame.h"

class SharedLineNumberTable {
public:
  int _size;
  void *_ptr;

  SharedLineNumberTable(int size, void *ptr) : _size(size), _ptr(ptr) {}
  ~SharedLineNumberTable();
};

class MethodInfo {
public:
  MethodInfo()
      : _mark(false), _is_entry(false), _referenced(false), _age(0), _key(0), _class(0),
        _name(0), _sig(0), _modifiers(0), _line_number_table(nullptr), _type() {}

  bool _mark;
  bool _is_entry;
  bool _referenced;  // Tracked during writeStackTraces() for cleanup
  int _age;          // Consecutive chunks without reference (0 = recently used)
  u32 _key;
  u32 _class;
  u32 _name;
  u32 _sig;
  jint _modifiers;
  std::shared_ptr<SharedLineNumberTable> _line_number_table;
  FrameTypeId _type;

  jint getLineNumber(jint bci) {
    // if the shared pointer is not pointing to the line number table, consider
    // size 0
    if (!_line_number_table || _line_number_table->_size == 0) {
      return 0;
    }

    int i = 1;
    int table_size = _line_number_table->_size;
    table_size = table_size > 0 ? table_size : - table_size;

    while (i < table_size &&
           bci >= ((jvmtiLineNumberEntry *)_line_number_table->_ptr)[i]
                      .start_location) {
      i++;
    }
    return ((jvmtiLineNumberEntry *)_line_number_table->_ptr)[i - 1]
        .line_number;
  }

  bool isHidden() {
    // 0x1400 = ACC_SYNTHETIC(0x1000) | ACC_BRIDGE(0x0040)
    return _modifiers == 0 || (_modifiers & 0x1040);
  }
};

// MethodMap's key can be derived from 3 sources:
// 1) jmethodID for Java methods
// 2) void* address for native method names
// 3) Encoded RemoteFrameInfo
// The values of the keys are potentially overlapping, so we use 
// the highest 2 bits to distinguish them.
// 00 - jmethodID
// 10 - void* address
// 01 - RemoteFrameInfo
class MethodMap : public std::map<unsigned long, MethodInfo> {
public:
  static constexpr unsigned long ADDRESS_MARK = 0x8000000000000000ULL;
  static constexpr unsigned long REMOTE_FRAME_MARK = 0x4000000000000000ULL;
  static constexpr unsigned long METHOD_MARK = 0xc000000000000000ULL;
  static constexpr unsigned long KEY_TYPE_MASK = ADDRESS_MARK | REMOTE_FRAME_MARK | METHOD_MARK;

  MethodMap() {}

  static unsigned long makeKey(jmethodID method) {
    unsigned long key = (unsigned long)method;
    assert((key & KEY_TYPE_MASK) == 0);
    return key;
  }

  static unsigned long makeKey(const char* addr) {
    unsigned long key = (unsigned long)addr;
    assert((key & KEY_TYPE_MASK) == 0);
    return (key | ADDRESS_MARK);
  }

  static unsigned long makeKey(unsigned long packed_remote_frame) {
    unsigned long key = packed_remote_frame;
    assert((key & KEY_TYPE_MASK) == 0);
    return (key | REMOTE_FRAME_MARK);
  }

  static unsigned long makeKey(const void* method) {
    unsigned long key = reinterpret_cast<unsigned long>(method);
    assert((key & KEY_TYPE_MASK) == 0);
    return (key | METHOD_MARK);
  }
};

#endif // _METHODINFO_H
