/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include "../../main/cpp/objectSampler.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "vmEntry.h"

static constexpr char OBJECT_SAMPLER_TEST_NAME[] = "ObjectSamplerTest";
class ObjectSamplerGlobalSetup {
public:
  ObjectSamplerGlobalSetup()  { installGtestCrashHandler<OBJECT_SAMPLER_TEST_NAME>(); }
  ~ObjectSamplerGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static ObjectSamplerGlobalSetup object_sampler_global_setup;

// ---------------------------------------------------------------------------
// ObjectSamplerTestAccessor — friend of ObjectSampler, exposes internals
// needed by the regression tests.
// ---------------------------------------------------------------------------
class ObjectSamplerTestAccessor {
public:
  static void setActive(ObjectSampler *s, bool v) {
    __atomic_store_n(&s->_active, v, __ATOMIC_RELEASE);
  }

  static void callRecordAllocation(ObjectSampler *s, jvmtiEnv *jvmti,
                                   JNIEnv *jni, jthread thread,
                                   int event_type, jobject object,
                                   jclass klass, jlong size) {
    s->recordAllocation(jvmti, jni, thread, event_type, object, klass, size);
  }
};

// ---------------------------------------------------------------------------
// Mock-JVMTI infrastructure for Deallocate regression tests
// ---------------------------------------------------------------------------

// Read-only buffer the success mocks hand back as a class signature; never
// modified, so file-scope storage is safe.
static char g_mock_class_name[] = "Ljava/lang/String;";

// Test fixture owning the per-test JVMTI function table and Deallocate
// counter. Each TEST_F gets a fresh instance, which (a) prevents shared
// static state from leaking between tests, (b) lets the fixture restore
// the process-global ObjectSampler _active flag in TearDown, and (c)
// removes the use-after-return hazard of returning a struct whose
// _jvmtiEnv::functions points into a per-call static.
class ObjectSamplerDeallocateTest : public ::testing::Test {
protected:
  jvmtiInterface_1_ tbl{};
  _jvmtiEnv mock_env{};
  int deallocate_calls = 0;

  static ObjectSamplerDeallocateTest *active_fixture;

  void SetUp() override {
    deallocate_calls = 0;
    tbl = jvmtiInterface_1_{};
    tbl.Deallocate = &mock_Deallocate;
    mock_env.functions = &tbl;
    active_fixture = this;
  }

  void TearDown() override {
    // Restore the process-global singleton flag so subsequent tests start
    // from a known state.
    ObjectSamplerTestAccessor::setActive(ObjectSampler::instance(), false);
    active_fixture = nullptr;
  }

  void setMockGetClassSignature(
      jvmtiError(JNICALL *fn)(jvmtiEnv *, jclass, char **, char **)) {
    tbl.GetClassSignature = fn;
  }

  void runAndExpect(
      jvmtiError(JNICALL *mock)(jvmtiEnv *, jclass, char **, char **),
      bool active, int expected_calls) {
    setMockGetClassSignature(mock);
    ObjectSampler *s = ObjectSampler::instance();
    ObjectSamplerTestAccessor::setActive(s, active);
    ObjectSamplerTestAccessor::callRecordAllocation(
        s, &mock_env, nullptr, nullptr, BCI_ALLOC, nullptr, nullptr, 1024);
    EXPECT_EQ(deallocate_calls, expected_calls);
  }

  static jvmtiError JNICALL mock_Deallocate(jvmtiEnv * /*env*/,
                                            unsigned char * /*mem*/) {
    ++active_fixture->deallocate_calls;
    return JVMTI_ERROR_NONE;
  }
};

ObjectSamplerDeallocateTest *
    ObjectSamplerDeallocateTest::active_fixture = nullptr;

static jvmtiError JNICALL mock_GetClassSignature_success(
    jvmtiEnv * /*env*/, jclass /*klass*/,
    char **signature_ptr, char ** /*generic_ptr*/) {
  if (signature_ptr) {
    *signature_ptr = g_mock_class_name;
  }
  return JVMTI_ERROR_NONE;
}

// Returns error but writes a non-NULL sentinel into *signature_ptr — the UAF
// scenario the fix guards against (Deallocate must not be called on error).
static jvmtiError JNICALL mock_GetClassSignature_error_with_sentinel(
    jvmtiEnv * /*env*/, jclass /*klass*/,
    char **signature_ptr, char ** /*generic_ptr*/) {
  if (signature_ptr) {
    *signature_ptr = g_mock_class_name;
  }
  return JVMTI_ERROR_INVALID_CLASS;
}

static jvmtiError JNICALL mock_GetClassSignature_error_null(
    jvmtiEnv * /*env*/, jclass /*klass*/,
    char **signature_ptr, char ** /*generic_ptr*/) {
  (void)signature_ptr;
  return JVMTI_ERROR_INVALID_CLASS;
}

static jvmtiError JNICALL mock_GetClassSignature_success_null_name(
    jvmtiEnv * /*env*/, jclass /*klass*/,
    char **signature_ptr, char ** /*generic_ptr*/) {
  if (signature_ptr) {
    *signature_ptr = NULL;
  }
  return JVMTI_ERROR_NONE;
}

// Regression tests for ObjectSampler::normalizeClassSignature, the
// guard that recordAllocation uses against null, empty, or malformed
// class signatures coming back from JVMTI.
TEST(ObjectSamplerTest, NormalizeRejectsNull) {
    const char *out_name = (const char *)0xdeadbeef;
    size_t out_len = 99;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature(NULL, &out_name, &out_len));
    // Outputs must be untouched when the call returns false.
    EXPECT_EQ(out_name, (const char *)0xdeadbeef);
    EXPECT_EQ(out_len, 99u);
}

TEST(ObjectSamplerTest, NormalizeRejectsEmpty) {
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("", &out_name, &out_len));
}

TEST(ObjectSamplerTest, NormalizeRejectsLoneL) {
    // Without the underflow guard, len - 2 would wrap to SIZE_MAX and
    // poison the lookupClass call.
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("L", &out_name, &out_len));
}

TEST(ObjectSamplerTest, NormalizeStripsLname) {
    const char *signature = "Ljava/lang/String;";
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_TRUE(ObjectSampler::normalizeClassSignature(signature, &out_name, &out_len));
    EXPECT_EQ(out_name, signature + 1);
    EXPECT_EQ(out_len, strlen("java/lang/String"));
}

TEST(ObjectSamplerTest, NormalizeRejectsLnameWithEmptyBody) {
    const char *out_name = (const char *)0xdeadbeef;
    size_t out_len = 99;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("L;", &out_name, &out_len));
    EXPECT_EQ(out_name, (const char *)0xdeadbeef);
    EXPECT_EQ(out_len, 99u);
}

TEST(ObjectSamplerTest, NormalizeRejectsLnameMissingTrailingSemicolon) {
    const char *out_name = (const char *)0xdeadbeef;
    size_t out_len = 99;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("Ljava/lang/String", &out_name, &out_len));
    EXPECT_EQ(out_name, (const char *)0xdeadbeef);
    EXPECT_EQ(out_len, 99u);
}

TEST(ObjectSamplerTest, NormalizeRejectsNullOutName) {
    size_t out_len = 0;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("Ljava/lang/String;", NULL, &out_len));
}

TEST(ObjectSamplerTest, NormalizeRejectsNullOutLen) {
    const char *out_name = nullptr;
    EXPECT_FALSE(ObjectSampler::normalizeClassSignature("Ljava/lang/String;", &out_name, NULL));
}

TEST(ObjectSamplerTest, NormalizePassesThroughPrimitiveArray) {
    const char *signature = "[B";
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_TRUE(ObjectSampler::normalizeClassSignature(signature, &out_name, &out_len));
    EXPECT_EQ(out_name, signature);
    EXPECT_EQ(out_len, strlen("[B"));
}

TEST(ObjectSamplerTest, NormalizePassesThroughObjectArray) {
    const char *signature = "[Ljava/lang/String;";
    const char *out_name = nullptr;
    size_t out_len = 0;
    EXPECT_TRUE(ObjectSampler::normalizeClassSignature(signature, &out_name, &out_len));
    // Array signatures are passed through verbatim - the leading 'L'
    // strip rule applies only when the very first character is 'L'.
    EXPECT_EQ(out_name, signature);
    EXPECT_EQ(out_len, strlen("[Ljava/lang/String;"));
}

// T-01: GetClassSignature returns error with non-NULL sentinel in *signature_ptr.
// Deallocate MUST NOT be called.
TEST_F(ObjectSamplerDeallocateTest, DeallocateNotCalledOnErrorWithNonNullSentinel) {
    runAndExpect(mock_GetClassSignature_error_with_sentinel, true, 0);
}

// T-02: GetClassSignature succeeds with a valid class name.
// Deallocate IS called exactly once (on the success path).
// Note: lookupClass returns -1 because the class map is empty, so the
// method returns without recording — that is the expected behaviour.
TEST_F(ObjectSamplerDeallocateTest, DeallocateCalledOnceOnGetClassSignatureSuccess) {
    runAndExpect(mock_GetClassSignature_success, true, 1);
}

// T-03: GetClassSignature fails and leaves class_name at NULL.
// Deallocate MUST NOT be called.
TEST_F(ObjectSamplerDeallocateTest, DeallocateNotCalledOnErrorWithNullName) {
    runAndExpect(mock_GetClassSignature_error_null, true, 0);
}

// T-04: GetClassSignature succeeds but writes NULL into *signature_ptr.
// Deallocate MUST NOT be called (the NULL guard in the condition fires).
TEST_F(ObjectSamplerDeallocateTest, DeallocateNotCalledWhenSuccessButNullName) {
    runAndExpect(mock_GetClassSignature_success_null_name, true, 0);
}

// T-05: _active is false — recordAllocation returns immediately.
// Deallocate MUST NOT be called.
TEST_F(ObjectSamplerDeallocateTest, DeallocateNotCalledWhenNotActive) {
    runAndExpect(mock_GetClassSignature_success, false, 0);
}
