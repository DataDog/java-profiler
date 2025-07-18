#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <signal.h>

#include "safeAccess.h"
#include "os.h"


static void (*orig_segvHandler)(int signo, siginfo_t *siginfo, void *ucontext);
static void (*orig_busHandler)(int signo, siginfo_t *siginfo, void *ucontext);


void signal_handle_wrapper(int signo, siginfo_t* siginfo, void* context) {
  if (!SafeAccess::handle_safefetch(signo, context)) {
    if (signo == SIGBUS && orig_busHandler != nullptr) {
       orig_busHandler(signo, siginfo, context);
    } else if (signo == SIGSEGV && orig_segvHandler != nullptr) {
       orig_segvHandler(signo, siginfo, context);
    }
  }
}

class SafeFetchTest : public ::testing::Test {
protected:
    void SetUp() override {
       orig_segvHandler = OS::replaceSigsegvHandler(signal_handle_wrapper);
       orig_busHandler = OS::replaceSigbusHandler(signal_handle_wrapper);
    }

    void TearDown() override {
       OS::replaceSigsegvHandler(orig_segvHandler);
       OS::replaceSigbusHandler(orig_busHandler);
    }
};


TEST_F(SafeFetchTest, validAccess32) {
  int i = 42;
  int* p = &i;
  int res = SafeAccess::safeFetch32(p, -1);
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
}

TEST_F(SafeFetchTest, invalidAccess64) {
  int64_t* p = nullptr;
  int64_t res = SafeAccess::safeFetch64(p, -1);
  EXPECT_EQ(res, -1);
  res = SafeAccess::safeFetch64(p, -2);
  EXPECT_EQ(res, -2);
}
