#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <climits>
#include <signal.h>

#include "safeAccess.h"
#include "os_dd.h"
#include "../../main/cpp/gtest_crash_handler.h"

// Test name for crash handler
static constexpr char SAFEFETCH_TEST_NAME[] = "SafeFetchTest";


static void (*orig_segvHandler)(int signo, siginfo_t *siginfo, void *ucontext);
static void (*orig_busHandler)(int signo, siginfo_t *siginfo, void *ucontext);


void signal_handle_wrapper(int signo, siginfo_t* siginfo, void* context) {
  if (!SafeAccess::handle_safefetch(signo, context)) {
    if (signo == SIGBUS && orig_busHandler != nullptr) {
       orig_busHandler(signo, siginfo, context);
    } else if (signo == SIGSEGV && orig_segvHandler != nullptr) {
       orig_segvHandler(signo, siginfo, context);
    } else {
       // If no original handler, use crash handler for debugging
       gtestCrashHandler(signo, siginfo, context, SAFEFETCH_TEST_NAME);
    }
  }
}

class SafeFetchTest : public ::testing::Test {
protected:
    void SetUp() override {
       orig_segvHandler = ddprof::OS::replaceSigsegvHandler(signal_handle_wrapper);
       orig_busHandler = ddprof::OS::replaceSigbusHandler(signal_handle_wrapper);
    }

    void TearDown() override {
       ddprof::OS::replaceSigsegvHandler(orig_segvHandler);
       ddprof::OS::replaceSigbusHandler(orig_busHandler);
    }
};


TEST_F(SafeFetchTest, validAccess32) {
  int i = 42;
  int* p = &i;
  int res = SafeAccess::safeFetch32(p, -1);
  EXPECT_EQ(res, i);
  i = INT_MAX;
  res = SafeAccess::safeFetch32(p, -1);
  EXPECT_EQ(res, i);
  i = INT_MIN;
  res = SafeAccess::safeFetch32(p, 0);
  EXPECT_EQ(res, i);
}


TEST_F(SafeFetchTest, invalidAccess32) {
  int* p = nullptr;
  int res = SafeAccess::safeFetch32(p, -1);
  EXPECT_EQ(res, -1);
  res = SafeAccess::safeFetch32(p, -2);
  EXPECT_EQ(res, -2);
}

TEST_F(SafeFetchTest, validAccess64) {
  int64_t i = 42;
  int64_t* p = &i;
  int64_t res = SafeAccess::safeFetch64(p, -1);
  EXPECT_EQ(res, i);
  i = LONG_MIN;
  res = SafeAccess::safeFetch64(p, -19);
  EXPECT_EQ(res, i);
  i = LONG_MAX;
  res = SafeAccess::safeFetch64(p, -1);
  EXPECT_EQ(res, i);
}

TEST_F(SafeFetchTest, invalidAccess64) {
  int64_t* p = nullptr;
  int64_t res = SafeAccess::safeFetch64(p, -1);
  EXPECT_EQ(res, -1);
  res = SafeAccess::safeFetch64(p, -2);
  EXPECT_EQ(res, -2);
}

TEST_F(SafeFetchTest, validAccessPtr) {
  char c = 'a';
  void* p = (void*)&c;
  void** pp = &p;
  void* res = SafeAccess::loadPtr(pp, nullptr);
  EXPECT_EQ(res, p);
}

TEST_F(SafeFetchTest, invalidAccessPtr) {
  int a, b;
  void* ap = (void*)&a;
  void* bp = (void*)&b;
  void** pp = nullptr;
  void* res = SafeAccess::loadPtr(pp, ap);
  EXPECT_EQ(res, ap);
  res = SafeAccess::loadPtr(pp, bp);
  EXPECT_EQ(res, bp);
}
