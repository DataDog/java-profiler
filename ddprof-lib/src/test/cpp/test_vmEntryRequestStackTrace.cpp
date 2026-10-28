/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Tests for VM::probeJFRRequestStackTrace() driven against a mock JVMTI
// environment (PROF-14757): the params null guard, and the publication rule
// that _request_stack_trace becomes observable (canRequestStackTrace() ==
// true) only after InitializeRequestStackTrace succeeded under jvmtistacks.

#include "gtest/gtest.h"

#include <cstdlib>
#include <cstring>
#include <vector>

#include "counters.h"
#include "referenceChainsTestAccessors.h"
#include "vmEntry.h"

namespace {

constexpr const char *REQUEST_ID = "com.sun.hotspot.functions.RequestStackTrace";
constexpr const char *INIT_ID = "com.sun.hotspot.functions.InitializeRequestStackTrace";

// Counts invocations of the mock InitializeRequestStackTrace extension.
int g_init_calls = 0;
// Counts mock Deallocate() invocations.
int g_dealloc_calls = 0;
// Error code returned by the mock InitializeRequestStackTrace extension.
jvmtiError g_init_result = JVMTI_ERROR_NONE;
// Function-table contents handed out by the mock GetExtensionFunctions.
std::vector<jvmtiExtensionFunctionInfo> g_ext_functions;
// Set to false to make the mock GetExtensionFunctions fail.
bool g_get_ext_ok = true;

// jvmtiExtensionFunction is a variadic function type; the mocks use the
// matching pure-variadic signature (their arguments are never inspected).
jvmtiError JNICALL mockInitializeRequestStackTrace(jvmtiEnv *env, ...) {
  g_init_calls++;
  return g_init_result;
}

jvmtiError JNICALL mockRequestStackTrace(jvmtiEnv *env, ...) {
  return JVMTI_ERROR_NONE;
}

jvmtiError JNICALL mockGetExtensionFunctions(jvmtiEnv *env, jint *count_ptr,
                                             jvmtiExtensionFunctionInfo **extensions) {
  if (!g_get_ext_ok) {
    return JVMTI_ERROR_INTERNAL;
  }
  *count_ptr = (jint)g_ext_functions.size();
  auto *infos = (jvmtiExtensionFunctionInfo *)malloc(
      sizeof(jvmtiExtensionFunctionInfo) * g_ext_functions.size());
  memcpy(infos, g_ext_functions.data(),
         sizeof(jvmtiExtensionFunctionInfo) * g_ext_functions.size());
  *extensions = infos;
  return JVMTI_ERROR_NONE;
}

jvmtiError JNICALL mockDeallocate(jvmtiEnv *env, unsigned char *mem) {
  g_dealloc_calls++;
  free(mem);
  return JVMTI_ERROR_NONE;
}

char *dupId(const char *id) { return strdup(id); }

// Builds one extension-function entry. param_count/params are explicit so a
// test can model a conformance-defect JVM (count > 0 with NULL params).
jvmtiExtensionFunctionInfo makeEntry(const char *id, jvmtiExtensionFunction fn,
                                     jint param_count = 0,
                                     jvmtiParamInfo *params = nullptr) {
  jvmtiExtensionFunctionInfo info = {};
  info.func = fn;
  info.id = dupId(id);
  info.short_description = dupId("mock");
  info.param_count = param_count;
  info.params = params;
  return info;
}

// Mock jvmtiEnv: in C++ jvmtiEnv is a struct whose first member is a pointer
// to the jvmtiInterface_1 function table (jvmti.h, struct _jvmtiEnv); a zeroed
// table with just GetExtensionFunctions and Deallocate installed is enough
// here. The mock env is byte-compatible with _jvmtiEnv because both lead with
// the same functions pointer and the wrappers only read it.
struct MockJvmti {
  jvmtiInterface_1 table = {};
  struct {
    const struct jvmtiInterface_1_ *functions;
  } env = {&table};

  MockJvmti() {
    table.GetExtensionFunctions = mockGetExtensionFunctions;
    table.Deallocate = mockDeallocate;
  }
};

class VmEntryRequestStackTraceTest : public ::testing::Test {
protected:
  void SetUp() override {
    saved_jvmti = VMTestAccessor::getJvmti();
    saved_request = VMTestAccessor::getRequestStackTrace();
    saved_init = VMTestAccessor::getInitRequestStackTrace();
    saved_jvmtistacks = VM::arguments()._jvmtistacks;

    g_init_calls = 0;
    g_dealloc_calls = 0;
    g_init_result = JVMTI_ERROR_NONE;
    g_get_ext_ok = true;
    g_ext_functions.clear();

    VMTestAccessor::setJvmti(nullptr);
    VMTestAccessor::setRequestStackTrace(nullptr);
    VMTestAccessor::setInitRequestStackTrace(nullptr);
  }

  void TearDown() override {
    VMTestAccessor::setJvmti(saved_jvmti);
    VMTestAccessor::setRequestStackTrace(saved_request);
    VMTestAccessor::setInitRequestStackTrace(saved_init);
    VM::arguments()._jvmtistacks = saved_jvmtistacks;
  }

  static MockJvmti *installMockJvmti() {
    static MockJvmti mock;
    VMTestAccessor::setJvmti(reinterpret_cast<jvmtiEnv *>(&mock.env));
    return &mock;
  }

  // Installs the mock and populates it with both HotSpot extension functions,
  // each owning a heap-allocated params array and names — every pointer the
  // production code hands to Deallocate must be a heap pointer, as with a
  // real JVMTI environment.
  void installBothExtensions() {
    installMockJvmti();
    for (const char *id : {REQUEST_ID, INIT_ID}) {
      auto *params = (jvmtiParamInfo *)malloc(sizeof(jvmtiParamInfo));
      params[0].name = strdup("mock.param");
      g_ext_functions.push_back(
          makeEntry(id, id == REQUEST_ID ? mockRequestStackTrace
                                         : mockInitializeRequestStackTrace,
                    1, params));
    }
  }

  jvmtiEnv *saved_jvmti;
  jvmtiExtensionFunction saved_request;
  jvmtiExtensionFunction saved_init;
  bool saved_jvmtistacks;
};

TEST_F(VmEntryRequestStackTraceTest, PublishedAfterSuccessfulInit) {
  installBothExtensions();
  VM::arguments()._jvmtistacks = true;

  VMTestAccessor::probeJFRRequestStackTrace();

  EXPECT_EQ(VMTestAccessor::getRequestStackTrace(), mockRequestStackTrace);
  EXPECT_EQ(VMTestAccessor::getInitRequestStackTrace(),
            mockInitializeRequestStackTrace);
  EXPECT_TRUE(VM::canRequestStackTrace());
  EXPECT_EQ(g_init_calls, 1);
  EXPECT_GT(g_dealloc_calls, 0);
}

TEST_F(VmEntryRequestStackTraceTest, NotPublishedWhenJvmtistacksDisabled) {
  installBothExtensions();
  VM::arguments()._jvmtistacks = false;

  VMTestAccessor::probeJFRRequestStackTrace();

  EXPECT_EQ(VMTestAccessor::getRequestStackTrace(), nullptr);
  EXPECT_EQ(VMTestAccessor::getInitRequestStackTrace(), nullptr);
  EXPECT_FALSE(VM::canRequestStackTrace());
  // Initialization must never run when jvmtistacks was not requested.
  EXPECT_EQ(g_init_calls, 0);
}

TEST_F(VmEntryRequestStackTraceTest, NotPublishedWhenInitFails) {
  installBothExtensions();
  VM::arguments()._jvmtistacks = true;
  g_init_result = JVMTI_ERROR_INTERNAL;
  long long failed_before = Counters::getCounter(JVMTI_STACKS_INIT_FAILED);

  VMTestAccessor::probeJFRRequestStackTrace();

  EXPECT_EQ(VMTestAccessor::getRequestStackTrace(), nullptr);
  // The init function stays published; only the request function must remain
  // unpublished so canRequestStackTrace() reports false.
  EXPECT_EQ(VMTestAccessor::getInitRequestStackTrace(),
            mockInitializeRequestStackTrace);
  EXPECT_FALSE(VM::canRequestStackTrace());
  EXPECT_EQ(Counters::getCounter(JVMTI_STACKS_INIT_FAILED), failed_before + 1);
}

TEST_F(VmEntryRequestStackTraceTest, NotPublishedWhenRequestExtensionMissing) {
  installMockJvmti();
  g_ext_functions.push_back(makeEntry(INIT_ID, mockInitializeRequestStackTrace));
  VM::arguments()._jvmtistacks = true;
  long long failed_before = Counters::getCounter(JVMTI_STACKS_INIT_FAILED);

  VMTestAccessor::probeJFRRequestStackTrace();

  EXPECT_EQ(VMTestAccessor::getRequestStackTrace(), nullptr);
  EXPECT_EQ(VMTestAccessor::getInitRequestStackTrace(), nullptr);
  EXPECT_FALSE(VM::canRequestStackTrace());
  EXPECT_EQ(Counters::getCounter(JVMTI_STACKS_INIT_FAILED), failed_before + 1);
  EXPECT_EQ(g_init_calls, 0);
}

TEST_F(VmEntryRequestStackTraceTest, NotPublishedWhenInitExtensionMissing) {
  installMockJvmti();
  g_ext_functions.push_back(makeEntry(REQUEST_ID, mockRequestStackTrace));
  VM::arguments()._jvmtistacks = true;
  long long failed_before = Counters::getCounter(JVMTI_STACKS_INIT_FAILED);

  VMTestAccessor::probeJFRRequestStackTrace();

  EXPECT_EQ(VMTestAccessor::getRequestStackTrace(), nullptr);
  EXPECT_EQ(VMTestAccessor::getInitRequestStackTrace(), nullptr);
  EXPECT_FALSE(VM::canRequestStackTrace());
  EXPECT_EQ(Counters::getCounter(JVMTI_STACKS_INIT_FAILED), failed_before + 1);
  EXPECT_EQ(g_init_calls, 0);
}

TEST_F(VmEntryRequestStackTraceTest, NotPublishedWhenGetExtensionFunctionsFails) {
  installMockJvmti();
  g_get_ext_ok = false;
  VM::arguments()._jvmtistacks = true;
  long long failed_before = Counters::getCounter(JVMTI_STACKS_INIT_FAILED);

  VMTestAccessor::probeJFRRequestStackTrace();

  EXPECT_EQ(VMTestAccessor::getRequestStackTrace(), nullptr);
  EXPECT_EQ(VMTestAccessor::getInitRequestStackTrace(), nullptr);
  EXPECT_FALSE(VM::canRequestStackTrace());
  EXPECT_EQ(Counters::getCounter(JVMTI_STACKS_INIT_FAILED), failed_before + 1);
}

// A conformance-defect JVM may report param_count > 0 with a NULL params
// array; the deallocation loop must not dereference it (PROF-14757 issue 3).
TEST_F(VmEntryRequestStackTraceTest, NullParamsWithNonZeroCountDoesNotCrash) {
  installMockJvmti();
  g_ext_functions.push_back(makeEntry(REQUEST_ID, mockRequestStackTrace,
                                      /*param_count=*/2, /*params=*/nullptr));
  g_ext_functions.push_back(makeEntry(INIT_ID, mockInitializeRequestStackTrace,
                                      /*param_count=*/0, /*params=*/nullptr));
  VM::arguments()._jvmtistacks = true;

  VMTestAccessor::probeJFRRequestStackTrace();

  EXPECT_EQ(VMTestAccessor::getRequestStackTrace(), mockRequestStackTrace);
  EXPECT_TRUE(VM::canRequestStackTrace());
}

} // namespace
