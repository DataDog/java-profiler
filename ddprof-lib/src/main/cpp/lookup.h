/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LOOKUP_H
#define _LOOKUP_H

#include "dictionary.h"
#include "vmEntry.h"

class MethodInfo;
class MethodMap;
class Recording;
class RemoteFrameInfo;

class Lookup {
public:
  Recording *_rec;
  MethodMap *_method_map;
  Dictionary *_classes;
  Dictionary _packages;
  Dictionary _symbols;

private:
  void fillNativeMethodInfo(MethodInfo *mi, const char *name,
                            const char *lib_name);
  void fillRemoteFrameInfo(MethodInfo *mi, const RemoteFrameInfo *rfi);
  void cutArguments(char *func);
  bool has_prefix(const char *str, const char *prefix) const {
    return strncmp(str, prefix, strlen(prefix)) == 0;
  }

  void fillJavaMethodInfo(MethodInfo *mi, jmethodID method, bool first_time);
  void fillMethodInfo(MethodInfo *mi, jclass method_class, char* class_name, char* method_name, char* method_sig,
                      jint line_number_table_size, jvmtiLineNumberEntry* line_number_table);
public:
  Lookup(Recording *rec, MethodMap *method_map, Dictionary *classes)
      : _rec(rec), _method_map(method_map), _classes(classes), _packages(),
        _symbols() {}

  MethodInfo *resolveMethod(ASGCT_CallFrame &frame);
  u32 getPackage(const char *class_name);
  u32 getSymbol(const char *name);
};

#endif // _LOOKUP_H
