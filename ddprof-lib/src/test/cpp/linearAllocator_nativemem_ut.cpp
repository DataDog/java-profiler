#include "gtest/gtest.h"
#include "linearAllocator.h"
#include "nativeMem.h"

// NM_CALLTRACE must track bytes actually handed out by alloc() -- i.e. touched,
// resident bytes -- not the virtual capacity of the mmap'd chunks backing them.
// The distinction is large: chunks are 8 MiB (CALL_TRACE_CHUNK) and alloc()
// eagerly reserves the next one at 50% fill, so a capacity-based counter
// over-reports by up to two chunks' worth of untouched address space.

static const size_t CHUNK_SIZE = 1024 * 1024;

class LinearAllocatorNativeMemTest : public ::testing::Test {
protected:
  long long _baseline[NM_NUM_CATEGORIES];

  // Static-duration objects elsewhere in the binary record into these same
  // categories before main() runs; restore their baseline in TearDown so
  // their destructors don't underflow a category this fixture zeroed.
  // (Same rationale as NativeMemTest in nativeMem_ut.cpp.)
  void SetUp() override {
    for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
      _baseline[c] = NativeMem::live((NativeMemCategory)c);
    }
    NativeMem::reset();
  }
  void TearDown() override {
    NativeMem::reset();
    for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
      NativeMem::setLive((NativeMemCategory)c, _baseline[c]);
    }
  }
};

TEST_F(LinearAllocatorNativeMemTest, ReportsBumpedBytesNotChunkCapacity) {
  const size_t ALLOC_SIZE = 128;
  const int NUM_ALLOCS = 100;

  LinearAllocator allocator(CHUNK_SIZE);
  // Constructing the allocator mmaps a chunk but touches nothing in it.
  EXPECT_EQ(0, NativeMem::live(NM_CALLTRACE))
      << "a freshly reserved chunk is untouched and must not be counted";

  for (int i = 0; i < NUM_ALLOCS; i++) {
    ASSERT_NE(nullptr, allocator.alloc(ALLOC_SIZE));
  }

  EXPECT_EQ((long long)(ALLOC_SIZE * NUM_ALLOCS), NativeMem::live(NM_CALLTRACE))
      << "live bytes must equal exactly the bytes alloc() handed out";
  EXPECT_LT(NativeMem::live(NM_CALLTRACE), (long long)CHUNK_SIZE)
      << "must not have jumped to whole-chunk granularity";
}

TEST_F(LinearAllocatorNativeMemTest, CrossingIntoASecondChunkStaysByteAccurate) {
  // An allocation size that does not divide the chunk evenly, driven past the
  // point where reserveChunk() pre-reserves the next chunk, so the reserved
  // chunk's untouched capacity would show up in a capacity-based counter.
  const size_t ALLOC_SIZE = 3000;
  const int NUM_ALLOCS = (int)(CHUNK_SIZE / ALLOC_SIZE) + 50;

  LinearAllocator allocator(CHUNK_SIZE);
  long long handed_out = 0;
  for (int i = 0; i < NUM_ALLOCS; i++) {
    if (allocator.alloc(ALLOC_SIZE) != nullptr) {
      handed_out += (long long)ALLOC_SIZE;
    }
  }

  EXPECT_EQ(handed_out, NativeMem::live(NM_CALLTRACE))
      << "byte-accurate across a chunk boundary, with a chunk pre-reserved";
}

TEST_F(LinearAllocatorNativeMemTest, ClearReturnsLiveToZero) {
  LinearAllocator allocator(CHUNK_SIZE);
  for (int i = 0; i < 50; i++) {
    ASSERT_NE(nullptr, allocator.alloc(256));
  }
  ASSERT_GT(NativeMem::live(NM_CALLTRACE), 0);

  allocator.clear();

  EXPECT_EQ(0, NativeMem::live(NM_CALLTRACE))
      << "clear() discards all chunk contents, including the retained _tail's";
}

TEST_F(LinearAllocatorNativeMemTest, FreeChunksReturnsLiveToZero) {
  LinearAllocator allocator(CHUNK_SIZE);
  for (int i = 0; i < 50; i++) {
    ASSERT_NE(nullptr, allocator.alloc(256));
  }
  long long before_detach = NativeMem::live(NM_CALLTRACE);
  ASSERT_GT(before_detach, 0);

  ChunkList detached = allocator.detachChunks();
  EXPECT_EQ(before_detach, NativeMem::live(NM_CALLTRACE))
      << "detaching moves ownership but frees nothing yet";

  LinearAllocator::freeChunks(detached);
  EXPECT_EQ(0, NativeMem::live(NM_CALLTRACE))
      << "freeing the detached chunks un-records exactly what alloc() recorded";
}
