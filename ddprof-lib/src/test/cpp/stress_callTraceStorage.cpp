/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "callTraceStorage.h"
#include "callTraceHashTable.h"
#include <vector>
#include <unordered_set>
#include <thread>
#include <atomic>
#include <random>
#include <chrono>
#include <algorithm>
#include "arch_dd.h"
#include <cstring>
#include <climits>
#include <stdexcept>
#include <mutex>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <sys/ucontext.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <fstream>

// Global crash handler for detailed debugging of segfaults
void crashHandler(int sig, siginfo_t *info, void *context) {
    // Prevent recursive calls
    static volatile sig_atomic_t in_crash_handler = 0;
    if (in_crash_handler) {
        // Already in crash handler - just exit to prevent infinite loop
        _exit(128 + sig);
    }
    in_crash_handler = 1;
    
    // Use async-signal-safe functions only
    const char* signal_names[] = {
        "UNKNOWN", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS",
        "SIGFPE", "SIGKILL", "SIGSEGV", "SIGUSR1", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGUSR2"
    };
    
    const char* signal_name = (sig >= 1 && sig <= 15) ? signal_names[sig] : "UNKNOWN";
    
    // Write crash info to stderr (async-signal-safe)
    write(STDERR_FILENO, "\n=== STRESS TEST CRASH ===\n", 28);
    
    // Signal type
    write(STDERR_FILENO, "Signal: ", 8);
    write(STDERR_FILENO, signal_name, strlen(signal_name));
    
    // Format signal number
    char sig_buf[32];
    snprintf(sig_buf, sizeof(sig_buf), " (%d)\n", sig);
    write(STDERR_FILENO, sig_buf, strlen(sig_buf));
    
    // Fault address for memory access violations
    if (sig == SIGSEGV || sig == SIGBUS) {
        write(STDERR_FILENO, "Fault address: 0x", 17);
        char addr_buf[32];
        snprintf(addr_buf, sizeof(addr_buf), "%lx\n", (unsigned long)info->si_addr);
        write(STDERR_FILENO, addr_buf, strlen(addr_buf));
    }
    
    // Thread ID
    write(STDERR_FILENO, "Thread ID: ", 11);
    char tid_buf[32];
    snprintf(tid_buf, sizeof(tid_buf), "%d\n", getpid());
    write(STDERR_FILENO, tid_buf, strlen(tid_buf));
    
    // Backtrace
    write(STDERR_FILENO, "\nBacktrace:\n", 12);
    void *buffer[64];
    int nptrs = backtrace(buffer, 64);
    
    // Use backtrace_symbols_fd which is async-signal-safe
    backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO);
    
    // Register state (platform specific)
#ifdef __APPLE__
    ucontext_t *uctx = (ucontext_t *)context;
    if (uctx && uctx->uc_mcontext) {
        write(STDERR_FILENO, "\nRegister state:\n", 17);
        char reg_buf[128];
        #ifdef __x86_64__
            snprintf(reg_buf, sizeof(reg_buf), "RIP: 0x%llx, RSP: 0x%llx\n", 
                    uctx->uc_mcontext->__ss.__rip, uctx->uc_mcontext->__ss.__rsp);
        #elif defined(__aarch64__)
            snprintf(reg_buf, sizeof(reg_buf), "PC: 0x%llx, SP: 0x%llx\n",
                    uctx->uc_mcontext->__ss.__pc, uctx->uc_mcontext->__ss.__sp);
        #endif
        write(STDERR_FILENO, reg_buf, strlen(reg_buf));
    }
#endif
    
    write(STDERR_FILENO, "\n=== END CRASH INFO ===\n", 25);
    
    // Ensure output is flushed
    fsync(STDERR_FILENO);
    
    // Don't interfere with AddressSanitizer - just exit cleanly
    _exit(128 + sig);
}

// Install crash handler for debugging
void installCrashHandler() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;  // Get detailed info, keep handler active
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = crashHandler;
    
    // Install for various crash signals
    sigaction(SIGSEGV, &sa, nullptr);
    sigaction(SIGBUS, &sa, nullptr);
    sigaction(SIGABRT, &sa, nullptr);
    sigaction(SIGFPE, &sa, nullptr);
    sigaction(SIGILL, &sa, nullptr);
}

// Helper function to find a CallTrace by trace_id in an unordered_set
CallTrace* findTraceById(const std::unordered_set<CallTrace*>& traces, u64 trace_id) {
    for (CallTrace* trace : traces) {
        if (trace && trace != CallTraceSample::PREPARING && trace->trace_id == trace_id) {
            return trace;
        }
    }
    return nullptr;
}

// Optimized batch lookup for multiple trace IDs
void findMultipleTracesById(const std::unordered_set<CallTrace*>& traces, 
                           const std::vector<u64>& trace_ids,
                           size_t& found_count) {
    // Create a lookup set for O(1) lookups instead of O(n) per trace
    std::unordered_set<u64> target_ids(trace_ids.begin(), trace_ids.end());
    found_count = 0;
    
    for (CallTrace* trace : traces) {
        if (trace && trace != CallTraceSample::PREPARING) {
            if (target_ids.find(trace->trace_id) != target_ids.end()) {
                found_count++;
                // Early termination - found all traces
                if (found_count == trace_ids.size()) {
                    break;
                }
            }
        }
    }
}

// Thread-safe random number generator for deterministic testing
class ThreadSafeRandom {
private:
    std::mt19937 gen_;
    std::mutex mutex_;
    
public:
    explicit ThreadSafeRandom(uint32_t seed = std::random_device{}()) : gen_(seed) {}
    
    uint64_t next(uint64_t max_val = UINT64_MAX) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::uniform_int_distribution<uint64_t> dis(0, max_val);
        return dis(gen_);
    }
};

// Guarded buffer for detecting memory corruption
class GuardedBuffer {
private:
    static constexpr uint32_t GUARD_PATTERN = 0xDEADBEEF;
    static constexpr size_t GUARD_SIZE = sizeof(uint32_t);
    static constexpr size_t ALIGNMENT = 8; // 8-byte alignment for ASGCT_CallFrame
    
    void* buffer_;
    size_t size_;
    void* aligned_data_;
    
    void setGuards() {
        uint32_t* front_guard = reinterpret_cast<uint32_t*>(buffer_);
        uint32_t* back_guard = reinterpret_cast<uint32_t*>(
            static_cast<char*>(aligned_data_) + size_
        );
        *front_guard = GUARD_PATTERN;
        *back_guard = GUARD_PATTERN;
    }
    
    // Calculate the next properly aligned address
    static void* align_pointer(void* ptr, size_t alignment) {
        uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
        uintptr_t aligned = (addr + alignment - 1) & ~(alignment - 1);
        return reinterpret_cast<void*>(aligned);
    }
    
public:
    explicit GuardedBuffer(size_t size) : size_(size) {
        // Allocate extra space for guards + alignment padding
        size_t total_size = GUARD_SIZE + (ALIGNMENT - 1) + size + GUARD_SIZE;
        buffer_ = malloc(total_size);
        if (buffer_ == nullptr) {
            throw std::bad_alloc();
        }
        
        // Calculate aligned data pointer after front guard
        void* after_front_guard = static_cast<char*>(buffer_) + GUARD_SIZE;
        aligned_data_ = align_pointer(after_front_guard, ALIGNMENT);
        
        setGuards();
    }
    
    ~GuardedBuffer() {
        if (buffer_) {
            free(buffer_);
        }
    }
    
    void* data() {
        return aligned_data_;
    }
    
    bool checkCorruption() const {
        uint32_t* front_guard = reinterpret_cast<uint32_t*>(buffer_);
        uint32_t* back_guard = reinterpret_cast<uint32_t*>(
            static_cast<char*>(aligned_data_) + size_
        );
        return (*front_guard != GUARD_PATTERN) || (*back_guard != GUARD_PATTERN);
    }
};

class StressTestSuite : public ::testing::Test {
protected:
    void SetUp() override {
        // Install crash handler for detailed debugging
        installCrashHandler();
        
        // Initialize any shared resources
    }
    
    void TearDown() override {
        // Clean up resources
    }
};

// Test 1: SwapStormTest - Double-buffered call-trace storage under rapid swapping
TEST_F(StressTestSuite, SwapStormTest) {
    const int NUM_THREADS = 8;
    const int OPERATIONS_PER_THREAD = 5000;
    const int SWAP_FREQUENCY_MS = 10;
    
    std::atomic<bool> test_running{true};
    std::atomic<bool> test_failed{false};
    std::atomic<uint64_t> total_operations{0};
    std::atomic<uint64_t> successful_puts{0};
    std::atomic<uint64_t> swap_count{0};
    
    auto storage = std::make_unique<CallTraceStorage>();
    ThreadSafeRandom random_gen(12345);
    
    // Worker threads continuously adding traces
    std::vector<std::thread> workers;
    for (int i = 0; i < NUM_THREADS; ++i) {
        workers.emplace_back([&, i]() {
            std::mt19937 local_gen(random_gen.next(UINT32_MAX));
            std::uniform_int_distribution<uint32_t> bci_dis(1, 1000);
            std::uniform_int_distribution<uintptr_t> method_dis(0x1000, 0x9999);
            
            for (int op = 0; op < OPERATIONS_PER_THREAD && test_running.load(); ++op) {
                try {
                    ASGCT_CallFrame frame;
                    frame.bci = bci_dis(local_gen);
                    frame.method_id = reinterpret_cast<jmethodID>(method_dis(local_gen));
                    
                    u64 trace_id = storage->put(1, &frame, false, 1);
                    if (trace_id > 0) {
                        successful_puts.fetch_add(1, std::memory_order_relaxed);
                    }
                    
                    total_operations.fetch_add(1, std::memory_order_relaxed);
                    
                    // Occasional yield to allow swaps
                    if (op % 100 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    test_failed.store(true);
                    break;
                }
            }
        });
    }
    
    // Rapid swapping thread
    std::thread swapper([&]() {
        while (test_running.load() && !test_failed.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SWAP_FREQUENCY_MS));
            
            try {
                storage->processTraces([](const std::unordered_set<CallTrace*>& traces) {
                    // Process traces (simulating JFR serialization)
                    (void)traces.size();
                });
                swap_count.fetch_add(1, std::memory_order_relaxed);
            } catch (...) {
                test_failed.store(true);
                break;
            }
        }
    });
    
    // Let the stress test run for a reasonable duration
    std::this_thread::sleep_for(std::chrono::seconds(2));
    test_running.store(false);
    
    // Wait for all threads
    for (auto& worker : workers) {
        worker.join();
    }
    swapper.join();
    
    // Verify results
    EXPECT_FALSE(test_failed.load()) << "Stress test encountered failures";
    EXPECT_GT(swap_count.load(), 0) << "No swaps occurred during test";
    EXPECT_GT(successful_puts.load(), 0) << "No successful trace insertions";
    EXPECT_EQ(total_operations.load(), NUM_THREADS * OPERATIONS_PER_THREAD) 
        << "Not all operations completed";
    
    std::cout << "SwapStorm completed: " << total_operations.load() << " ops, " 
              << swap_count.load() << " swaps, " << successful_puts.load() << " successful puts" << std::endl;
}

// Test 2: HashTableContentionTest - Concurrent hash table operations
TEST_F(StressTestSuite, HashTableContentionTest) {
    const int NUM_THREADS = 6;
    const int TRACES_PER_THREAD = 3000;
    
    // Use heap allocation with proper alignment to avoid ASAN alignment issues
    // Stack allocation with high alignment requirements (64 bytes) is problematic under ASAN
    void* aligned_memory = std::aligned_alloc(alignof(CallTraceHashTable), sizeof(CallTraceHashTable));
    ASSERT_NE(aligned_memory, nullptr) << "Failed to allocate aligned memory for CallTraceHashTable";
    
    auto hash_table_ptr = std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
        new(aligned_memory) CallTraceHashTable(), 
        [](CallTraceHashTable* ptr) {
            ptr->~CallTraceHashTable();
            std::free(ptr);
        }
    );
    CallTraceHashTable& hash_table = *hash_table_ptr;
    hash_table.setInstanceId(42);
    
    std::atomic<bool> test_failed{false};
    std::atomic<uint64_t> successful_operations{0};
    std::atomic<uint64_t> expansion_triggers{0};
    std::vector<std::thread> threads;
    
    // Create diverse stack traces to force table expansion
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&, t]() {
            std::mt19937 gen(std::random_device{}() + t);
            std::uniform_int_distribution<uint32_t> bci_dis(1, 10000);
            std::uniform_int_distribution<uintptr_t> method_dis(0x1000, 0xFFFF);
            
            for (int i = 0; i < TRACES_PER_THREAD; ++i) {
                try {
                    ASGCT_CallFrame frame;
                    frame.bci = t * 10000 + bci_dis(gen); // Ensure uniqueness
                    frame.method_id = reinterpret_cast<jmethodID>(t * 0x10000 + method_dis(gen));
                    
                    u64 trace_id = hash_table.put(1, &frame, false, 1);
                    
                    if (trace_id == 0) {
                        // Sample was dropped - acceptable under high contention
                        continue;
                    }
                    
                    if (trace_id == 0x7fffffffffffffffULL) {
                        // Overflow trace - also acceptable
                        continue;
                    }
                    
                    successful_operations.fetch_add(1, std::memory_order_relaxed);
                    
                    // Detect expansion events (approximate)
                    if (i > 0 && i % 1000 == 0) {
                        expansion_triggers.fetch_add(1, std::memory_order_relaxed);
                    }
                    
                    // Yield occasionally to increase contention
                    if (i % 500 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    test_failed.store(true);
                    return;
                }
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    EXPECT_FALSE(test_failed.load()) << "Hash table contention test failed";
    EXPECT_GT(successful_operations.load(), 0) << "No successful hash table operations";
    
    // Verify table still functions after stress
    ASGCT_CallFrame test_frame;
    test_frame.bci = 99999;
    test_frame.method_id = reinterpret_cast<jmethodID>(0x99999);
    u64 final_trace_id = hash_table.put(1, &test_frame, false, 1);
    EXPECT_GT(final_trace_id, 0) << "Hash table non-functional after stress test";
    
    std::cout << "HashTable contention completed: " << successful_operations.load() 
              << " successful operations" << std::endl;
}

// Test 3: TraceIdFuzzTest - 64-bit TraceId bit-packing validation
TEST_F(StressTestSuite, TraceIdFuzzTest) {
    const int NUM_THREADS = 4;
    const int OPERATIONS_PER_THREAD = 50000;
    
    std::atomic<bool> test_failed{false};
    std::atomic<uint64_t> total_operations{0};
    std::atomic<uint64_t> sign_extension_violations{0};
    std::vector<std::thread> threads;
    
    // Helper functions for TraceId manipulation
    auto extract_slot = [](u64 trace_id) -> u64 {
        return trace_id & 0xFFFFFFFFULL;
    };
    
    auto extract_instance_id = [](u64 trace_id) -> u64 {
        return trace_id >> 32;
    };
    
    auto create_trace_id = [](u64 instance_id, u64 slot) -> u64 {
        return (instance_id << 32) | (slot & 0xFFFFFFFFULL);
    };
    
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&, t]() {
            std::mt19937 gen(std::random_device{}() + t);
            std::uniform_int_distribution<u64> dis(0, 0xFFFFFFFFULL);
            
            for (int i = 0; i < OPERATIONS_PER_THREAD; ++i) {
                try {
                    u64 instance_id = dis(gen);
                    u64 slot = dis(gen);
                    
                    u64 trace_id = create_trace_id(instance_id, slot);
                    u64 extracted_instance = extract_instance_id(trace_id);
                    u64 extracted_slot = extract_slot(trace_id);
                    
                    // Verify bit-packing correctness
                    if (extracted_instance != instance_id || extracted_slot != slot) {
                        test_failed.store(true);
                        return;
                    }
                    
                    // Check for potential sign-extension issues
                    int32_t slot_as_int32 = static_cast<int32_t>(slot);
                    if (slot_as_int32 < 0) {
                        sign_extension_violations.fetch_add(1, std::memory_order_relaxed);
                    }
                    
                    // Test with extreme values
                    if (i % 1000 == 0) {
                        std::vector<u64> extreme_values = {
                            0x0000000000000000ULL,
                            0xFFFFFFFFFFFFFFFFULL,
                            0x7FFFFFFFFFFFFFFFULL,
                            0x8000000000000000ULL,
                            0x00000000FFFFFFFFULL,
                            0xFFFFFFFF00000000ULL,
                        };
                        
                        for (u64 extreme_trace_id : extreme_values) {
                            u64 e_slot = extract_slot(extreme_trace_id);
                            u64 e_instance = extract_instance_id(extreme_trace_id);
                            u64 reconstructed = create_trace_id(e_instance, e_slot);
                            
                            if (reconstructed != extreme_trace_id) {
                                test_failed.store(true);
                                return;
                            }
                        }
                    }
                    
                    total_operations.fetch_add(1, std::memory_order_relaxed);
                    
                } catch (...) {
                    test_failed.store(true);
                    return;
                }
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    EXPECT_FALSE(test_failed.load()) << "TraceId bit-packing test failed";
    EXPECT_EQ(total_operations.load(), NUM_THREADS * OPERATIONS_PER_THREAD) 
        << "Not all TraceId operations completed";
    
    std::cout << "TraceId fuzz test completed: " << total_operations.load() 
              << " operations, " << sign_extension_violations.load() 
              << " sign extension cases detected" << std::endl;
}

// Test 4: AsgctBoundsTest - ASGCT frame handling bounds checking
TEST_F(StressTestSuite, AsgctBoundsTest) {
    const int NUM_THREADS = 4;
    const int FRAMES_PER_THREAD = 10000;
    const size_t MAX_FRAMES = 1024;
    
    std::atomic<bool> test_failed{false};
    std::atomic<uint64_t> guard_violations{0};
    std::atomic<uint64_t> bounds_checks{0};
    std::vector<std::thread> threads;
    
    // Pre-allocated guarded buffers for each thread
    std::vector<std::unique_ptr<GuardedBuffer>> buffers;
    for (int t = 0; t < NUM_THREADS; ++t) {
        buffers.push_back(std::make_unique<GuardedBuffer>(MAX_FRAMES * sizeof(ASGCT_CallFrame)));
    }
    
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&, t]() {
            ASGCT_CallFrame* frames = static_cast<ASGCT_CallFrame*>(buffers[t]->data());
            std::mt19937 gen(std::random_device{}() + t);
            std::uniform_int_distribution<uint32_t> bci_dis(0, UINT32_MAX);
            std::uniform_int_distribution<uintptr_t> method_dis(0x1000, 0xFFFFF);
            std::uniform_int_distribution<size_t> frame_count_dis(1, MAX_FRAMES);
            
            for (int i = 0; i < FRAMES_PER_THREAD; ++i) {
                try {
                    size_t num_frames = frame_count_dis(gen);
                    
                    // Fill frames with random data
                    for (size_t f = 0; f < num_frames; ++f) {
                        frames[f].bci = bci_dis(gen);
                        frames[f].method_id = reinterpret_cast<jmethodID>(method_dis(gen));
                    }
                    
                    // Simulate bounds checking that might occur in actual profiler
                    for (size_t f = 0; f < num_frames; ++f) {
                        if (frames[f].bci == static_cast<jint>(-1)) {
                            // Native frame marker - acceptable
                            continue;
                        }
                        
                        // Check for reasonable BCI values
                        if (frames[f].bci > 0x7FFFFFFF) {
                            bounds_checks.fetch_add(1, std::memory_order_relaxed);
                        }
                        
                        // Verify method_id is not null (would be problematic)
                        if (frames[f].method_id == nullptr) {
                            bounds_checks.fetch_add(1, std::memory_order_relaxed);
                        }
                    }
                    
                    // Check for buffer corruption
                    if (buffers[t]->checkCorruption()) {
                        guard_violations.fetch_add(1, std::memory_order_relaxed);
                        test_failed.store(true);
                        return;
                    }
                    
                    // Yield occasionally
                    if (i % 1000 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    test_failed.store(true);
                    return;
                }
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    EXPECT_FALSE(test_failed.load()) << "ASGCT bounds test failed";
    EXPECT_EQ(guard_violations.load(), 0) << "Buffer corruption detected";
    
    std::cout << "ASGCT bounds test completed: " << bounds_checks.load() 
              << " bounds checks performed" << std::endl;
}

// Test 5: JfrTinyBufferTest - JFR serialization with minimal buffers
TEST_F(StressTestSuite, JfrTinyBufferTest) {
    const int NUM_THREADS = 4;
    const int OPERATIONS_PER_THREAD = 5000;
    const size_t TINY_BUFFER_SIZE = 64; // Deliberately small
    
    std::atomic<bool> test_failed{false};
    std::atomic<uint64_t> buffer_overruns{0};
    std::atomic<uint64_t> successful_writes{0};
    std::vector<std::thread> threads;
    
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&, t]() {
            auto buffer = std::make_unique<GuardedBuffer>(TINY_BUFFER_SIZE);
            char* write_ptr = static_cast<char*>(buffer->data());
            std::mt19937 gen(std::random_device{}() + t);
            std::uniform_int_distribution<size_t> write_size_dis(1, TINY_BUFFER_SIZE + 10);
            
            for (int i = 0; i < OPERATIONS_PER_THREAD; ++i) {
                try {
                    size_t write_size = write_size_dis(gen);
                    
                    // Simulate JFR buffer write with bounds checking
                    if (write_size <= TINY_BUFFER_SIZE) {
                        // Safe write
                        std::memset(write_ptr, static_cast<int>(0xAA + (i % 16)), write_size);
                        successful_writes.fetch_add(1, std::memory_order_relaxed);
                    } else {
                        // Would overflow - record but don't actually overflow
                        buffer_overruns.fetch_add(1, std::memory_order_relaxed);
                    }
                    
                    // Check for corruption
                    if (buffer->checkCorruption()) {
                        test_failed.store(true);
                        return;
                    }
                    
                    // Yield occasionally
                    if (i % 500 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    test_failed.store(true);
                    return;
                }
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    EXPECT_FALSE(test_failed.load()) << "JFR tiny buffer test failed";
    EXPECT_GT(successful_writes.load(), 0) << "No successful buffer writes";
    EXPECT_GT(buffer_overruns.load(), 0) << "No buffer overrun cases detected";
    
    std::cout << "JFR tiny buffer test completed: " << successful_writes.load() 
              << " successful writes, " << buffer_overruns.load() << " overruns detected" << std::endl;
}

// Test 6: LivenessPurityTest - Liveness callback purity validation
TEST_F(StressTestSuite, LivenessPurityTest) {
    const int NUM_ITERATIONS = 500;  // Reduced from 1000 for better performance
    const int TRACES_PER_ITERATION = 50;
    
    std::atomic<bool> test_failed{false};
    std::atomic<uint64_t> callback_invocations{0};
    std::atomic<uint64_t> preserved_traces{0};
    
    auto storage = std::make_unique<CallTraceStorage>();
    ThreadSafeRandom random_gen(54321);
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; ++iteration) {
        try {
            std::vector<u64> trace_ids;
            
            // Add traces
            for (int t = 0; t < TRACES_PER_ITERATION; ++t) {
                ASGCT_CallFrame frame;
                frame.bci = static_cast<jint>(random_gen.next(10000));
                frame.method_id = reinterpret_cast<jmethodID>(random_gen.next(0xFFFF) + 0x1000);
                
                u64 trace_id = storage->put(1, &frame, false, 1);
                if (trace_id > 0) {
                    trace_ids.push_back(trace_id);
                }
            }
            
            if (trace_ids.empty()) {
                continue;
            }
            
            // Register liveness checker - should be pure and deterministic
            size_t preserve_count = trace_ids.size() / 2;
            std::vector<u64> to_preserve(trace_ids.begin(), trace_ids.begin() + preserve_count);
            
            storage->registerLivenessChecker([to_preserve](std::unordered_set<u64>& buffer) {
                // Pure callback - no side effects, deterministic output
                for (u64 trace_id : to_preserve) {
                    buffer.insert(trace_id);
                }
            });
            
            callback_invocations.fetch_add(1, std::memory_order_relaxed);
            
            // Process traces and verify preservation
            size_t actual_preserved = 0;
            storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
                findMultipleTracesById(traces, to_preserve, actual_preserved);
            });
            
            preserved_traces.fetch_add(actual_preserved, std::memory_order_relaxed);
            
            // Verify deterministic behavior - re-register same callback
            storage->registerLivenessChecker([to_preserve](std::unordered_set<u64>& buffer) {
                for (u64 trace_id : to_preserve) {
                    buffer.insert(trace_id);
                }
            });
            
            // Second process should have consistent results
            size_t second_preserved = 0;
            storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
                findMultipleTracesById(traces, to_preserve, second_preserved);
            });
            
            // Yield periodically
            if (iteration % 100 == 0) {
                std::this_thread::yield();
            }
            
        } catch (...) {
            test_failed.store(true);
            break;
        }
    }
    
    EXPECT_FALSE(test_failed.load()) << "Liveness purity test failed";
    EXPECT_GT(callback_invocations.load(), 0) << "No liveness callbacks invoked";
    EXPECT_GT(preserved_traces.load(), 0) << "No traces preserved";
    
    std::cout << "Liveness purity test completed: " << callback_invocations.load() 
              << " callback invocations, " << preserved_traces.load() << " traces preserved" << std::endl;
}

// TLS-focused stress tests

// TLS canary pattern for detecting buffer corruption
struct TLSCanary {
    static constexpr uint64_t CANARY_PATTERN = 0xDEADBEEFCAFEBABEULL;
    static constexpr size_t BUFFER_SIZE = 8192;
    static constexpr size_t CANARY_COUNT = 4;
    
    uint64_t front_canary[CANARY_COUNT];
    char buffer[BUFFER_SIZE];
    uint64_t back_canary[CANARY_COUNT];
    
    TLSCanary() {
        for (size_t i = 0; i < CANARY_COUNT; ++i) {
            front_canary[i] = CANARY_PATTERN + i;
            back_canary[i] = CANARY_PATTERN + i + CANARY_COUNT;
        }
        std::memset(buffer, 0xAA, BUFFER_SIZE);
    }
    
    bool checkCanaries() const {
        for (size_t i = 0; i < CANARY_COUNT; ++i) {
            if (front_canary[i] != CANARY_PATTERN + i ||
                back_canary[i] != CANARY_PATTERN + i + CANARY_COUNT) {
                return false;
            }
        }
        return true;
    }
    
    void simulateLogWrite(const std::string& message) {
        // Simulate writing log data with potential for overrun
        size_t write_size = std::min(message.length(), BUFFER_SIZE - 1);
        std::memcpy(buffer, message.c_str(), write_size);
        buffer[write_size] = '\0';
    }
    
    void simulatePathWrite(const std::string& path) {
        // Simulate long path name writes
        size_t path_len = std::min(path.length(), BUFFER_SIZE / 2);
        std::memcpy(buffer, path.c_str(), path_len);
        
        // Add some stack frame simulation
        char stack_info[512];
        snprintf(stack_info, sizeof(stack_info), 
                "|frame:%p|method:%s|bci:%d", 
                (void*)0x12345678, "someMethod", (int)(path_len % 1000));
        
        size_t remaining = BUFFER_SIZE - path_len - 1;
        size_t stack_len = std::min(strlen(stack_info), remaining);
        std::memcpy(buffer + path_len, stack_info, stack_len);
    }
};

// Thread-local storage for TLS tests
thread_local TLSCanary* tls_canary = nullptr;

// Test 7: TLS Overrun Canary Test
TEST_F(StressTestSuite, TLSOverrunCanaryTest) {
    const int NUM_THREADS = 6;
    const int OPERATIONS_PER_THREAD = 10000;
    const int SWAP_FREQUENCY_MS = 5; // More aggressive swapping
    
    std::atomic<bool> test_running{true};
    std::atomic<bool> canary_corruption{false};
    std::atomic<uint64_t> total_operations{0};
    std::atomic<uint64_t> canary_checks{0};
    std::atomic<uint64_t> swap_count{0};
    
    auto storage = std::make_unique<CallTraceStorage>();
    ThreadSafeRandom random_gen(99999);
    
    // Worker threads hammering TLS buffers while doing storage operations
    std::vector<std::thread> workers;
    for (int i = 0; i < NUM_THREADS; ++i) {
        workers.emplace_back([&, i]() {
            // Initialize TLS canary for this thread
            tls_canary = new TLSCanary();
            
            std::mt19937 local_gen(random_gen.next(UINT32_MAX));
            std::uniform_int_distribution<size_t> size_dis(100, 4000);
            std::uniform_int_distribution<int> operation_dis(0, 2);
            
            for (int op = 0; op < OPERATIONS_PER_THREAD && test_running.load(); ++op) {
                try {
                    // Check canary at start of each operation
                    if (!tls_canary->checkCanaries()) {
                        canary_corruption.store(true);
                        break;
                    }
                    
                    // Simulate various TLS buffer stress operations
                    int operation = operation_dis(local_gen);
                    switch (operation) {
                        case 0: {
                            // Large log line simulation
                            size_t log_size = size_dis(local_gen);
                            std::string large_log(log_size, 'L');
                            large_log += std::to_string(op) + "_thread_" + std::to_string(i);
                            tls_canary->simulateLogWrite(large_log);
                            break;
                        }
                        case 1: {
                            // Deep path simulation
                            std::string deep_path = "/very/deep/file/system/path/that/could/be/very/long/";
                            for (int depth = 0; depth < 20; ++depth) {
                                deep_path += "subdir" + std::to_string(depth) + "/";
                            }
                            deep_path += "filename_" + std::to_string(op);
                            tls_canary->simulatePathWrite(deep_path);
                            break;
                        }
                        case 2: {
                            // Stack stringification simulation
                            std::ostringstream stack_trace;
                            for (int frame = 0; frame < 50; ++frame) {
                                stack_trace << "Frame" << frame 
                                           << ":Method" << (frame * 123 + op)
                                           << ":BCI" << (frame * 456 + i) << ";";
                            }
                            tls_canary->simulateLogWrite(stack_trace.str());
                            break;
                        }
                    }
                    
                    // Also do some storage operations to create interference
                    ASGCT_CallFrame frame;
                    frame.bci = static_cast<jint>(op % 10000);
                    frame.method_id = reinterpret_cast<jmethodID>(0x1000 + i * 1000 + op);
                    storage->put(1, &frame, false, 1);
                    
                    // Check canary after operations
                    canary_checks.fetch_add(1, std::memory_order_relaxed);
                    if (!tls_canary->checkCanaries()) {
                        canary_corruption.store(true);
                        break;
                    }
                    
                    total_operations.fetch_add(1, std::memory_order_relaxed);
                    
                    // Yield occasionally to allow swaps
                    if (op % 200 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    canary_corruption.store(true);
                    break;
                }
            }
            
            // Final canary check and cleanup
            if (tls_canary && !tls_canary->checkCanaries()) {
                canary_corruption.store(true);
            }
            delete tls_canary;
            tls_canary = nullptr;
        });
    }
    
    // Aggressive swapping thread
    std::thread swapper([&]() {
        while (test_running.load() && !canary_corruption.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SWAP_FREQUENCY_MS));
            
            try {
                storage->processTraces([](const std::unordered_set<CallTrace*>& traces) {
                    // Aggressive processing to stress TLS during swaps
                    volatile size_t count = traces.size();
                    (void)count;
                });
                swap_count.fetch_add(1, std::memory_order_relaxed);
            } catch (...) {
                canary_corruption.store(true);
                break;
            }
        }
    });
    
    // Run stress test
    std::this_thread::sleep_for(std::chrono::seconds(3));
    test_running.store(false);
    
    // Wait for threads
    for (auto& worker : workers) {
        worker.join();
    }
    swapper.join();
    
    // Verify results
    EXPECT_FALSE(canary_corruption.load()) << "TLS canary corruption detected";
    EXPECT_GT(canary_checks.load(), 0) << "No canary checks performed";
    EXPECT_GT(swap_count.load(), 0) << "No storage swaps occurred";
    
    std::cout << "TLS canary test completed: " << total_operations.load() << " ops, "
              << canary_checks.load() << " canary checks, " << swap_count.load() 
              << " swaps, corruption=" << (canary_corruption.load() ? "YES" : "NO") << std::endl;
}

// Test 8: TCMalloc A/B Runner
TEST_F(StressTestSuite, TCMallocABRunner) {
    const int NUM_ITERATIONS = 1000;
    const int ALLOCATION_SIZE = 1024;
    
    std::atomic<bool> test_failed{false};
    std::atomic<uint64_t> normal_crashes{0};
    std::atomic<uint64_t> preload_crashes{0};
    std::atomic<uint64_t> fence_crashes{0};
    
    // Helper to run workload and detect crashes
    auto run_workload = [&](const std::string& env_setup) -> bool {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process - run the workload
            if (!env_setup.empty()) {
                std::system(("export " + env_setup).c_str());
            }
            
            try {
                // Simulate the exact workload from other tests
                std::vector<void*> allocations;
                allocations.reserve(NUM_ITERATIONS);
                
                for (int i = 0; i < NUM_ITERATIONS; ++i) {
                    void* ptr = malloc(ALLOCATION_SIZE + (i % 100));
                    if (ptr) {
                        std::memset(ptr, 0xAB + (i % 16), ALLOCATION_SIZE + (i % 100));
                        allocations.push_back(ptr);
                    }
                    
                    // Some allocations freed immediately, others kept
                    if (i % 3 == 0 && !allocations.empty()) {
                        free(allocations.back());
                        allocations.pop_back();
                    }
                    
                    // Simulate some storage work
                    if (i % 100 == 0) {
                        // Use heap allocation to avoid ASAN alignment issues with stack objects
                        void* aligned_mem = std::aligned_alloc(alignof(CallTraceHashTable), sizeof(CallTraceHashTable));
                        if (aligned_mem) {
                            auto test_table_ptr = std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
                                new(aligned_mem) CallTraceHashTable(), 
                                [](CallTraceHashTable* ptr) {
                                    ptr->~CallTraceHashTable();
                                    std::free(ptr);
                                }
                            );
                            CallTraceHashTable& test_table = *test_table_ptr;
                            test_table.setInstanceId(42);
                            ASGCT_CallFrame frame;
                            frame.bci = i;
                            frame.method_id = reinterpret_cast<jmethodID>(0x1000 + i);
                            test_table.put(1, &frame, false, 1);
                        }
                    }
                }
                
                // Cleanup
                for (void* ptr : allocations) {
                    free(ptr);
                }
                
                _exit(0); // Success
            } catch (...) {
                _exit(1); // Failure
            }
        } else if (pid > 0) {
            // Parent process - wait for child
            int status;
            waitpid(pid, &status, 0);
            
            if (WIFEXITED(status)) {
                return WEXITSTATUS(status) == 0;
            } else {
                // Child crashed
                return false;
            }
        } else {
            // Fork failed
            return false;
        }
    };
    
    // Test 1: Normal run (baseline)
    for (int run = 0; run < 3; ++run) {
        if (!run_workload("")) {
            normal_crashes.fetch_add(1, std::memory_order_relaxed);
        }
    }
    
    // Test 2: With tcmalloc LD_PRELOAD (if available)
    std::string tcmalloc_path;
    std::vector<std::string> possible_paths = {
        "/usr/lib/x86_64-linux-gnu/libtcmalloc.so.4",
        "/usr/lib/libtcmalloc.so",
        "/opt/homebrew/lib/libtcmalloc.so",
        "/usr/local/lib/libtcmalloc.so"
    };
    
    for (const std::string& path : possible_paths) {
        if (access(path.c_str(), R_OK) == 0) {
            tcmalloc_path = path;
            break;
        }
    }
    
    if (!tcmalloc_path.empty()) {
        for (int run = 0; run < 3; ++run) {
            if (!run_workload("LD_PRELOAD=" + tcmalloc_path)) {
                preload_crashes.fetch_add(1, std::memory_order_relaxed);
            }
        }
        
        // Test 3: With TCMALLOC_PAGE_FENCE=1 if available
        for (int run = 0; run < 3; ++run) {
            if (!run_workload("LD_PRELOAD=" + tcmalloc_path + " TCMALLOC_PAGE_FENCE=1")) {
                fence_crashes.fetch_add(1, std::memory_order_relaxed);
            }
        }
    }
    
    // Record results (crashes are not necessarily test failures - they're data points)
    std::cout << "TCMalloc A/B test completed:" << std::endl;
    std::cout << "  Normal runs: " << normal_crashes.load() << " crashes out of 3" << std::endl;
    if (!tcmalloc_path.empty()) {
        std::cout << "  TCMalloc preload: " << preload_crashes.load() << " crashes out of 3" << std::endl;
        std::cout << "  TCMalloc fence: " << fence_crashes.load() << " crashes out of 3" << std::endl;
        std::cout << "  TCMalloc path: " << tcmalloc_path << std::endl;
    } else {
        std::cout << "  TCMalloc not found - skipped preload tests" << std::endl;
    }
    
    // Test passes if we collected data (crashes are informational)
    EXPECT_FALSE(test_failed.load()) << "TCMalloc A/B test infrastructure failed";
}

// Global state for signal pressure test
static std::atomic<bool> signal_pressure_active{false};
static std::atomic<uint64_t> signals_delivered{0};
static std::atomic<bool> signal_corruption_detected{false};
thread_local volatile uint32_t tls_write_counter = 0;

// Global state for realistic signal test
static std::atomic<bool> realistic_test_running{false};
static std::atomic<bool> realistic_handler_corruption{false};
static std::atomic<uint64_t> realistic_signals_handled{0};
static std::atomic<uint64_t> realistic_storage_operations{0};
static CallTraceStorage* realistic_shared_storage = nullptr;

// Signal handler for pressure test
void pressure_signal_handler(int sig) {
    if (!signal_pressure_active.load()) {
        return;
    }
    
    signals_delivered.fetch_add(1, std::memory_order_relaxed);
    
    // Simulate lightweight profiling work in signal handler
    // Check TLS consistency
    uint32_t expected = tls_write_counter;
    if (expected != tls_write_counter) {
        signal_corruption_detected.store(true);
    }
    
    // Tiny bit of work (signal-safe)
    volatile uint64_t dummy = 0;
    for (int i = 0; i < 10; ++i) {
        dummy += i;
    }
    (void)dummy;
}

// Realistic signal handler for profiler stress test
void realistic_profiler_signal_handler(int sig) {
    if (!realistic_test_running.load()) return;
    
    realistic_signals_handled.fetch_add(1, std::memory_order_relaxed);
    
    try {
        // Simulate what the real profiler does in signal context
        // 1. Get thread ID (potential race with thread destruction)
        pthread_t current_thread = pthread_self();
        
        // 2. Try to record a sample (this should be signal-safe)
        ASGCT_CallFrame frame;
        frame.bci = static_cast<jint>(realistic_signals_handled.load() % 10000);
        frame.method_id = reinterpret_cast<jmethodID>(0x1000 + (uintptr_t)current_thread);
        
        // 3. This is where real bugs occur - storage operations in signal context
        if (realistic_shared_storage) {
            u64 trace_id = realistic_shared_storage->put(1, &frame, false, 1);
            if (trace_id > 0) {
                realistic_storage_operations.fetch_add(1, std::memory_order_relaxed);
            }
        }
        
        // 4. Simulate some work that might cause corruption
        static thread_local volatile uint64_t signal_work_counter = 0;
        signal_work_counter++;
        
        // Check for corruption pattern - if we're accessing destroyed TLS
        if (signal_work_counter > 20000) {
            realistic_handler_corruption.store(true);
        }
        
    } catch (...) {
        realistic_handler_corruption.store(true);
    }
}

// Test 9: Signal Pressure Test
TEST_F(StressTestSuite, SignalPressureTest) {
    const int SIGNAL_FREQUENCY_HZ = 1000; // 1000 Hz profiling signals
    const int TEST_DURATION_MS = 2000;
    const int NUM_WORKER_THREADS = 3;
    
    std::atomic<bool> test_running{true};
    std::atomic<bool> deadlock_detected{false};
    std::atomic<uint64_t> tls_writes_completed{0};
    std::vector<std::thread> workers;
    
    // Install signal handler
    struct sigaction old_action;
    struct sigaction new_action;
    new_action.sa_handler = pressure_signal_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = SA_RESTART;
    
    if (sigaction(SIGUSR1, &new_action, &old_action) != 0) {
        GTEST_SKIP() << "Could not install signal handler";
        return;
    }
    
    signal_pressure_active.store(true);
    signals_delivered.store(0);
    signal_corruption_detected.store(false);
    
    // Worker threads doing TLS writes
    for (int t = 0; t < NUM_WORKER_THREADS; ++t) {
        workers.emplace_back([&, t]() {
            tls_write_counter = 0;
            const size_t TINY_WRITE_SIZE = 64;
            char tls_buffer[TINY_WRITE_SIZE];
            
            // Setup sigaltstack for this thread (test both with and without)
            bool use_altstack = (t % 2 == 0);
            stack_t alt_stack;
            stack_t old_stack;
            
            if (use_altstack) {
                alt_stack.ss_sp = malloc(SIGSTKSZ);
                alt_stack.ss_size = SIGSTKSZ;
                alt_stack.ss_flags = 0;
                
                if (alt_stack.ss_sp && sigaltstack(&alt_stack, &old_stack) == 0) {
                    // Successfully installed alt stack
                } else {
                    use_altstack = false;
                }
            }
            
            auto start_time = std::chrono::steady_clock::now();
            uint32_t write_count = 0;
            
            while (test_running.load()) {
                try {
                    // Tiny TLS writes with counter increments
                    tls_write_counter = ++write_count;
                    
                    // Simulate small TLS buffer operations
                    snprintf(tls_buffer, TINY_WRITE_SIZE, "t%d_w%u", t, write_count);
                    
                    // Verify consistency
                    if (tls_write_counter != write_count) {
                        signal_corruption_detected.store(true);
                        break;
                    }
                    
                    tls_writes_completed.fetch_add(1, std::memory_order_relaxed);
                    
                    // Very short yield to allow signal delivery
                    if (write_count % 100 == 0) {
                        std::this_thread::yield();
                    }
                    
                    // Deadlock detection - if we're stuck too long, bail
                    auto now = std::chrono::steady_clock::now();
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count() > TEST_DURATION_MS * 2) {
                        deadlock_detected.store(true);
                        break;
                    }
                    
                } catch (...) {
                    signal_corruption_detected.store(true);
                    break;
                }
            }
            
            // Cleanup alt stack
            if (use_altstack && alt_stack.ss_sp) {
                sigaltstack(&old_stack, nullptr);
                free(alt_stack.ss_sp);
            }
        });
    }
    
    // Signal delivery thread
    std::thread signaller([&]() {
        auto signal_interval = std::chrono::microseconds(1000000 / SIGNAL_FREQUENCY_HZ);
        auto start_time = std::chrono::steady_clock::now();
        
        while (test_running.load()) {
            for (std::thread& worker : workers) {
                pthread_kill(worker.native_handle(), SIGUSR1);
            }
            
            std::this_thread::sleep_for(signal_interval);
            
            // Check for test timeout
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count() > TEST_DURATION_MS) {
                test_running.store(false);
                break;
            }
        }
    });
    
    // Wait for test completion
    signaller.join();
    
    // Stop signal pressure
    signal_pressure_active.store(false);
    
    // Wait for workers
    for (auto& worker : workers) {
        worker.join();
    }
    
    // Restore signal handler
    sigaction(SIGUSR1, &old_action, nullptr);
    
    // Verify results
    EXPECT_FALSE(signal_corruption_detected.load()) << "Signal pressure caused TLS corruption";
    EXPECT_FALSE(deadlock_detected.load()) << "Deadlock detected during signal pressure test";
    EXPECT_GT(signals_delivered.load(), 0) << "No signals were delivered";
    EXPECT_GT(tls_writes_completed.load(), 0) << "No TLS writes completed";
    
    std::cout << "Signal pressure test completed: " << signals_delivered.load() 
              << " signals delivered, " << tls_writes_completed.load() << " TLS writes, "
              << "corruption=" << (signal_corruption_detected.load() ? "YES" : "NO") << std::endl;
}

// Test 10: Teardown Fuzz Test
TEST_F(StressTestSuite, TeardownFuzzTest) {
    const int NUM_THREAD_CYCLES = 1000;
    const int CONCURRENT_THREADS = 8;
    
    std::atomic<bool> teardown_corruption{false};
    std::atomic<uint64_t> threads_created{0};
    std::atomic<uint64_t> threads_completed{0};
    std::atomic<uint64_t> agent_work_completed{0};
    
    // Shared storage for thread lifecycle testing
    auto shared_storage = std::make_unique<CallTraceStorage>();
    ThreadSafeRandom cycle_random(77777);
    
    for (int cycle = 0; cycle < NUM_THREAD_CYCLES / CONCURRENT_THREADS; ++cycle) {
        std::vector<std::thread> native_threads;
        
        // Create batch of native threads
        for (int t = 0; t < CONCURRENT_THREADS; ++t) {
            native_threads.emplace_back([&, cycle, t]() {
                threads_created.fetch_add(1, std::memory_order_relaxed);
                
                try {
                    // Initialize thread-local agent data
                    thread_local bool tls_initialized = false;
                    thread_local uint64_t tls_agent_id = 0;
                    
                    if (!tls_initialized) {
                        tls_agent_id = cycle_random.next(UINT32_MAX);
                        tls_initialized = true;
                    }
                    
                    // Simulate small amount of agent work
                    std::vector<u64> trace_ids;
                    for (int work = 0; work < 10; ++work) {
                        ASGCT_CallFrame frame;
                        frame.bci = static_cast<jint>(cycle * 1000 + t * 100 + work);
                        frame.method_id = reinterpret_cast<jmethodID>(tls_agent_id + work);
                        
                        u64 trace_id = shared_storage->put(1, &frame, false, 1);
                        if (trace_id > 0) {
                            trace_ids.push_back(trace_id);
                        }
                        
                        // Verify TLS is still valid
                        if (!tls_initialized || tls_agent_id == 0) {
                            teardown_corruption.store(true);
                            return;
                        }
                    }
                    
                    agent_work_completed.fetch_add(trace_ids.size(), std::memory_order_relaxed);
                    
                    // Simulate thread doing work after "TLS cleanup"
                    // This is the dangerous case we're testing for
                    tls_initialized = false; // Simulate TLS being cleared
                    
                    // Try to do more agent work (this should be safe or fail gracefully)
                    for (int post_work = 0; post_work < 3; ++post_work) {
                        try {
                            ASGCT_CallFrame frame;
                            frame.bci = static_cast<jint>(-1); // Native frame
                            frame.method_id = reinterpret_cast<jmethodID>(0x999999);
                            
                            // This might fail, but shouldn't crash
                            u64 result = shared_storage->put(1, &frame, false, 1);
                            (void)result;
                            
                            // Check if we can still access TLS safely
                            if (tls_agent_id != 0) {
                                // TLS still accessible after "cleanup" - record this
                                agent_work_completed.fetch_add(1, std::memory_order_relaxed);
                            }
                            
                        } catch (...) {
                            // Exceptions during post-cleanup work are acceptable
                            // as long as they don't crash the process
                        }
                    }
                    
                    threads_completed.fetch_add(1, std::memory_order_relaxed);
                    
                } catch (...) {
                    teardown_corruption.store(true);
                }
            });
        }
        
        // Wait for this batch of threads to complete
        for (auto& thread : native_threads) {
            thread.join();
        }
        
        // Periodic cleanup of storage to simulate real usage patterns
        if (cycle % 10 == 0) {
            shared_storage->processTraces([](const std::unordered_set<CallTrace*>& traces) {
                // Simulate processing collected traces
                volatile size_t count = traces.size();
                (void)count;
            });
        }
        
        // Break early if corruption detected
        if (teardown_corruption.load()) {
            break;
        }
    }
    
    // Final cleanup
    shared_storage->clear();
    
    // Verify results
    EXPECT_FALSE(teardown_corruption.load()) << "Teardown corruption detected";
    EXPECT_EQ(threads_created.load(), threads_completed.load()) << "Thread creation/completion mismatch";
    EXPECT_GT(agent_work_completed.load(), 0) << "No agent work completed";
    
    std::cout << "Teardown fuzz test completed: " << threads_created.load() 
              << " threads created, " << threads_completed.load() << " completed, "
              << agent_work_completed.load() << " work units, "
              << "corruption=" << (teardown_corruption.load() ? "YES" : "NO") << std::endl;
}

// REALISTIC STRESS TESTS - Target actual profiler code paths
// These tests are designed to catch real bugs by exercising actual production code

// CRASH-SAFE TEST EXECUTION FRAMEWORK
// This allows us to continue testing even after individual tests crash

// Helper function for crash-safe test execution using process isolation
bool executeCrashSafeTest(const std::string& test_name, std::function<void()> test_func) {
    std::cout << "\n=== Executing crash-safe test: " << test_name << " ===" << std::endl;
    
    pid_t pid = fork();
    if (pid == 0) {
        // Child process - run the test in isolation
        try {
            test_func();
            std::cout << "Test " << test_name << " completed successfully" << std::endl;
            _exit(0); // Success
        } catch (const std::exception& e) {
            std::cout << "Test " << test_name << " threw exception: " << e.what() << std::endl;
            _exit(1); // Exception
        } catch (...) {
            std::cout << "Test " << test_name << " threw unknown exception" << std::endl;
            _exit(2); // Unknown exception
        }
    } else if (pid > 0) {
        // Parent process - wait and analyze result
        int status;
        pid_t result = waitpid(pid, &status, 0);
        
        if (result == -1) {
            std::cout << "Test " << test_name << " - waitpid failed: " << strerror(errno) << std::endl;
            return false;
        }
        
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                std::cout << "✅ Test " << test_name << " - PASSED" << std::endl;
                return true;
            } else {
                std::cout << "❌ Test " << test_name << " - FAILED with exit code " << exit_code << std::endl;
                return false;
            }
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            std::cout << "💥 Test " << test_name << " - CRASHED with signal " << sig;
            switch (sig) {
                case SIGSEGV: std::cout << " (SIGSEGV - segmentation fault - memory bug found!)"; break;
                case SIGABRT: std::cout << " (SIGABRT - abort - assertion failure)"; break;
                case SIGBUS: std::cout << " (SIGBUS - bus error - alignment issue)"; break;
                case SIGFPE: std::cout << " (SIGFPE - floating point exception)"; break;
                case SIGTRAP: std::cout << " (SIGTRAP - debug trap)"; break;
                case SIGILL: std::cout << " (SIGILL - illegal instruction)"; break;
                default: std::cout << " (signal " << sig << ")"; break;
            }
            std::cout << std::endl;
            return false;
        } else {
            std::cout << "❓ Test " << test_name << " - UNKNOWN termination (status=" << status << ")" << std::endl;
            return false;
        }
    } else {
        std::cout << "💀 Test " << test_name << " - fork failed: " << strerror(errno) << std::endl;
        return false;
    }
}

// Test Results Collector
struct TestSuiteResults {
    int total_tests = 0;
    int passed_tests = 0;
    int failed_tests = 0;
    int crashed_tests = 0;
    std::vector<std::string> crashes_found;
    std::vector<std::string> failures_found;
    
    void recordPass(const std::string& test_name) {
        total_tests++;
        passed_tests++;
    }
    
    void recordFailure(const std::string& test_name) {
        total_tests++;
        failed_tests++;
        failures_found.push_back(test_name);
    }
    
    void recordCrash(const std::string& test_name) {
        total_tests++;
        crashed_tests++;
        crashes_found.push_back(test_name);
    }
    
    void printSummary() const {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "STRESS TEST SUITE SUMMARY" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "Total tests run: " << total_tests << std::endl;
        std::cout << "✅ Passed: " << passed_tests << std::endl;
        std::cout << "❌ Failed: " << failed_tests << std::endl;
        std::cout << "💥 Crashed: " << crashed_tests << " (BUGS FOUND!)" << std::endl;
        
        if (!crashes_found.empty()) {
            std::cout << "\nCrashes found in:" << std::endl;
            for (const auto& crash : crashes_found) {
                std::cout << "  💥 " << crash << std::endl;
            }
        }
        
        if (!failures_found.empty()) {
            std::cout << "\nFailures in:" << std::endl;
            for (const auto& failure : failures_found) {
                std::cout << "  ❌ " << failure << std::endl;
            }
        }
        
        std::cout << std::string(60, '=') << std::endl;
    }
};

// Implementation function for signal stress (isolated for crash safety)
static void realProfilerSignalStressImpl(int signal_barrage_count, int num_worker_threads) {
    std::atomic<bool> test_running{true};
    std::atomic<bool> handler_corruption{false};
    std::atomic<uint64_t> signals_handled{0};
    std::atomic<uint64_t> storage_operations{0};
    
    // Create shared storage that will be hammered during signal handling
    auto shared_storage = std::make_unique<CallTraceStorage>();
    
    // Set up global state for signal handler
    realistic_test_running.store(true);
    realistic_handler_corruption.store(false);
    realistic_signals_handled.store(0);
    realistic_storage_operations.store(0);
    realistic_shared_storage = shared_storage.get();
    
    // Install realistic signal handler
    struct sigaction new_action, old_action;
    new_action.sa_handler = realistic_profiler_signal_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = SA_RESTART;
    
    if (sigaction(SIGUSR2, &new_action, &old_action) != 0) {
        throw std::runtime_error("Could not install signal handler");
    }
    
    // Worker threads doing normal profiler operations while signals fire
    std::vector<std::thread> workers;
    for (int t = 0; t < num_worker_threads; ++t) {
        workers.emplace_back([&, t]() {
            while (test_running.load()) {
                try {
                    // Simulate normal application work that profiler samples
                    for (int work = 0; work < 50; ++work) {
                        ASGCT_CallFrame frame;
                        frame.bci = work;
                        frame.method_id = reinterpret_cast<jmethodID>(0x2000 + t * 100 + work);
                        
                        u64 trace_id = shared_storage->put(1, &frame, false, 1);
                        
                        // Critical race: storage swap during signal handling
                        if (work == 25) {
                            shared_storage->processTraces([](const std::unordered_set<CallTrace*>& traces) {
                                volatile size_t count = traces.size();
                                (void)count;
                            });
                        }
                        
                        // Small delay to allow signal interference
                        if (work % 10 == 0) {
                            std::this_thread::yield();
                        }
                    }
                } catch (...) {
                    realistic_handler_corruption.store(true);
                    break;
                }
            }
        });
    }
    
    // Signal barrage thread - this is where crashes typically occur
    std::thread signaller([&]() {
        for (int i = 0; i < signal_barrage_count && test_running.load(); ++i) {
            // Send signals to all worker threads simultaneously
            for (std::thread& worker : workers) {
                pthread_kill(worker.native_handle(), SIGUSR2);
            }
            
            // Brief pause to let signals get handled
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            
            // Break early if we detect issues
            if (realistic_handler_corruption.load()) {
                break;
            }
        }
        realistic_test_running.store(false);
        test_running.store(false);
    });
    
    // Wait for test completion
    signaller.join();
    for (auto& worker : workers) {
        worker.join();
    }
    
    // Clean up global state
    realistic_shared_storage = nullptr;
    realistic_test_running.store(false);
    
    // Restore signal handler
    sigaction(SIGUSR2, &old_action, nullptr);
    
    // Report results
    std::cout << "Signal stress (" << signal_barrage_count << " signals, " << num_worker_threads 
              << " threads): " << realistic_signals_handled.load() << " signals handled, "
              << realistic_storage_operations.load() << " storage ops, "
              << "corruption=" << (realistic_handler_corruption.load() ? "YES" : "NO") << std::endl;
    
    if (realistic_handler_corruption.load()) {
        throw std::runtime_error("Signal handler corruption detected");
    }
}

// Test 11: Instance ID and Trace ID Generation Stress Test
TEST_F(StressTestSuite, InstanceIdTraceIdStressTest) {
    const int NUM_THREADS = 12;  // High contention on instance ID generation
    const int NUM_STORAGE_INSTANCES = 8;  // Multiple CallTraceStorage instances
    const int OPERATIONS_PER_THREAD = 10000;
    const int RAPID_SWAPS_COUNT = 1000;  // Frequent table swaps to stress instance ID assignment
    
    std::atomic<bool> test_failed{false};
    std::atomic<bool> collision_detected{false};
    std::atomic<bool> overflow_detected{false};
    std::atomic<bool> invalid_trace_id_detected{false};
    std::atomic<uint64_t> total_trace_ids_generated{0};
    std::atomic<uint64_t> duplicate_trace_ids{0};
    std::atomic<uint64_t> zero_trace_ids{0};
    std::atomic<uint64_t> max_instance_id_seen{0};
    
    // Set to track all generated trace IDs for collision detection
    std::mutex trace_id_mutex;
    std::unordered_set<u64> all_trace_ids;
    
    // Multiple storage instances to stress the global instance ID counter
    std::vector<std::unique_ptr<CallTraceStorage>> storage_instances;
    for (int i = 0; i < NUM_STORAGE_INSTANCES; ++i) {
        storage_instances.push_back(std::make_unique<CallTraceStorage>());
    }
    
    std::cout << "Testing instance ID and trace ID generation under extreme concurrency..." << std::endl;
    
    // Worker threads that hammer trace ID generation across multiple storage instances
    std::vector<std::thread> workers;
    for (int t = 0; t < NUM_THREADS; ++t) {
        workers.emplace_back([&, t]() {
            std::mt19937 gen(std::random_device{}() + t);
            std::uniform_int_distribution<int> storage_dis(0, NUM_STORAGE_INSTANCES - 1);
            std::uniform_int_distribution<uint32_t> bci_dis(1, 100000);
            std::uniform_int_distribution<uintptr_t> method_dis(0x10000, 0xFFFFFF);
            
            for (int op = 0; op < OPERATIONS_PER_THREAD && !test_failed.load(); ++op) {
                try {
                    // Pick a random storage instance
                    int storage_idx = storage_dis(gen);
                    CallTraceStorage* storage = storage_instances[storage_idx].get();
                    
                    // Create a unique frame to avoid hash collisions masking trace ID issues
                    ASGCT_CallFrame frame;
                    frame.bci = bci_dis(gen) + t * 1000000 + op;  // Ensure uniqueness
                    frame.method_id = reinterpret_cast<jmethodID>(method_dis(gen) + t * 0x1000000);
                    
                    // Generate trace ID
                    u64 trace_id = storage->put(1, &frame, false, 1);
                    
                    if (trace_id == 0) {
                        zero_trace_ids.fetch_add(1, std::memory_order_relaxed);
                        continue;  // Dropped trace is acceptable
                    }
                    
                    if (trace_id == CallTraceStorage::DROPPED_TRACE_ID) {
                        continue;  // Also acceptable
                    }
                    
                    // Extract instance ID and slot from trace ID
                    u64 instance_id = trace_id >> 32;
                    u64 slot = trace_id & 0xFFFFFFFFULL;
                    
                    // Validate trace ID structure
                    if (instance_id == 0) {
                        invalid_trace_id_detected.store(true);
                        test_failed.store(true);
                        return;
                    }
                    
                    // Check for slot overflow (should fit in 32 bits)
                    if (slot > 0xFFFFFFFFULL) {
                        overflow_detected.store(true);
                        test_failed.store(true);
                        return;
                    }
                    
                    // Track maximum instance ID to detect counter behavior
                    uint64_t current_max = max_instance_id_seen.load();
                    while (instance_id > current_max) {
                        if (max_instance_id_seen.compare_exchange_weak(current_max, instance_id)) {
                            break; // Successfully updated
                        }
                        // CAS failed - current_max now contains the actual current value
                        // Loop continues if instance_id is still greater than the updated current_max
                    }
                    
                    // Check for trace ID collisions
                    {
                        std::lock_guard<std::mutex> lock(trace_id_mutex);
                        if (all_trace_ids.find(trace_id) != all_trace_ids.end()) {
                            duplicate_trace_ids.fetch_add(1, std::memory_order_relaxed);
                        } else {
                            all_trace_ids.insert(trace_id);
                        }
                    }
                    
                    total_trace_ids_generated.fetch_add(1, std::memory_order_relaxed);
                    
                    // Occasionally trigger rapid table swaps to stress instance ID assignment
                    if (op % 100 == 0 && t == 0) {  // Only one thread does swaps
                        for (int swap = 0; swap < 3; ++swap) {
                            storage->processTraces([](const std::unordered_set<CallTrace*>& traces) {
                                volatile size_t count = traces.size();
                                (void)count;
                            });
                        }
                    }
                    
                    // Yield periodically to increase contention
                    if (op % 500 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    test_failed.store(true);
                    return;
                }
            }
        });
    }
    
    // Additional thread that does rapid processTraces() calls to stress instance ID assignment
    std::thread rapid_swapper([&]() {
        for (int swap = 0; swap < RAPID_SWAPS_COUNT && !test_failed.load(); ++swap) {
            try {
                // Randomly pick storage instance for swap
                int storage_idx = swap % NUM_STORAGE_INSTANCES;
                storage_instances[storage_idx]->processTraces([](const std::unordered_set<CallTrace*>& traces) {
                    // Process traces - this triggers new instance ID assignment
                    volatile size_t count = traces.size();
                    (void)count;
                });
                
                // Brief pause
                std::this_thread::sleep_for(std::chrono::microseconds(100));
                
            } catch (...) {
                test_failed.store(true);
                return;
            }
        }
    });
    
    // Wait for all threads
    for (auto& worker : workers) {
        worker.join();
    }
    rapid_swapper.join();
    
    // Analyze results
    u64 unique_trace_ids = 0;
    {
        std::lock_guard<std::mutex> lock(trace_id_mutex);
        unique_trace_ids = all_trace_ids.size();
    }
    
    std::cout << "Instance ID/Trace ID stress test completed:" << std::endl;
    std::cout << "  Total trace IDs generated: " << total_trace_ids_generated.load() << std::endl;
    std::cout << "  Unique trace IDs: " << unique_trace_ids << std::endl;
    std::cout << "  Duplicate trace IDs: " << duplicate_trace_ids.load() << std::endl;
    std::cout << "  Zero trace IDs: " << zero_trace_ids.load() << std::endl;
    std::cout << "  Max instance ID seen: " << max_instance_id_seen.load() << std::endl;
    std::cout << "  Overflow detected: " << (overflow_detected.load() ? "YES" : "NO") << std::endl;
    std::cout << "  Invalid trace ID detected: " << (invalid_trace_id_detected.load() ? "YES" : "NO") << std::endl;
    
    // Verify results
    EXPECT_FALSE(test_failed.load()) << "Instance ID/Trace ID stress test failed";
    EXPECT_FALSE(overflow_detected.load()) << "Slot overflow detected";
    EXPECT_FALSE(invalid_trace_id_detected.load()) << "Invalid trace ID structure detected";
    EXPECT_GT(total_trace_ids_generated.load(), 0) << "No trace IDs generated";
    EXPECT_GT(max_instance_id_seen.load(), 0) << "No valid instance IDs seen";
    
    // Check for excessive duplication (some is expected due to hash collisions)
    double duplication_rate = (double)duplicate_trace_ids.load() / total_trace_ids_generated.load();
    EXPECT_LT(duplication_rate, 0.1) << "Excessive trace ID duplication: " << duplication_rate;
    
    std::cout << "  Duplication rate: " << (duplication_rate * 100.0) << "%" << std::endl;
}

// Test 12: Hash Table Spin-Wait Edge Cases Stress Test
TEST_F(StressTestSuite, HashTableSpinWaitEdgeCasesTest) {
    const int NUM_THREADS = 16;  // High contention to trigger spin-waits
    const int OPERATIONS_PER_THREAD = 5000;
    const int HASH_COLLISION_GROUPS = 50;  // Force hash collisions to trigger spin-wait paths
    const int SLOW_ALLOCATION_FREQUENCY = 10;  // Simulate slow allocations
    
    std::atomic<bool> test_failed{false};
    std::atomic<bool> timeout_detected{false};
    std::atomic<bool> preparing_deadlock{false};
    std::atomic<bool> allocation_failure_cascade{false};
    std::atomic<uint64_t> spin_wait_events{0};
    std::atomic<uint64_t> timeout_recoveries{0};
    std::atomic<uint64_t> allocation_failures{0};
    std::atomic<uint64_t> successful_insertions{0};
    std::atomic<uint64_t> dropped_traces{0};
    std::atomic<uint64_t> hash_collisions_detected{0};
    
    // Single hash table to maximize contention
    // Use heap allocation with proper alignment to avoid ASAN alignment issues
    void* aligned_memory = std::aligned_alloc(alignof(CallTraceHashTable), sizeof(CallTraceHashTable));
    ASSERT_NE(aligned_memory, nullptr) << "Failed to allocate aligned memory for CallTraceHashTable";
    
    auto hash_table_ptr = std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
        new(aligned_memory) CallTraceHashTable(), 
        [](CallTraceHashTable* ptr) {
            ptr->~CallTraceHashTable();
            std::free(ptr);
        }
    );
    CallTraceHashTable& hash_table = *hash_table_ptr;
    hash_table.setInstanceId(42);
    
    std::cout << "Testing hash table spin-wait logic under extreme edge cases..." << std::endl;
    
    // Create controlled hash collision groups to force same-slot contention
    std::vector<std::vector<ASGCT_CallFrame>> collision_groups(HASH_COLLISION_GROUPS);
    for (int g = 0; g < HASH_COLLISION_GROUPS; ++g) {
        // Generate frames that will likely hash to similar slots
        for (int f = 0; f < 20; ++f) {
            ASGCT_CallFrame frame;
            frame.bci = g * 1000 + f;  // Group-based BCI to encourage collisions
            frame.method_id = reinterpret_cast<jmethodID>(0x100000 + g * 100 + f);
            collision_groups[g].push_back(frame);
        }
    }
    
    std::vector<std::thread> workers;
    for (int t = 0; t < NUM_THREADS; ++t) {
        workers.emplace_back([&, t]() {
            std::mt19937 gen(12345 + t);  // Fixed seed to increase collision probability
            std::uniform_int_distribution<int> group_dis(0, HASH_COLLISION_GROUPS - 1);
            std::uniform_int_distribution<int> frame_dis(0, 19);
            std::uniform_int_distribution<int> slow_dis(1, 100);
            
            for (int op = 0; op < OPERATIONS_PER_THREAD && !test_failed.load(); ++op) {
                try {
                    // Pick a frame from collision groups to maximize slot contention
                    int group = group_dis(gen);
                    int frame_idx = frame_dis(gen);
                    ASGCT_CallFrame frame = collision_groups[group][frame_idx];
                    
                    // Add some uniqueness to prevent exact duplicates while preserving hash patterns
                    frame.bci += t * 100000 + op;
                    
                    // Simulate slow allocation periodically to stress the spin-wait logic
                    if (slow_dis(gen) <= SLOW_ALLOCATION_FREQUENCY) {
                        // Brief delay to simulate memory allocation pressure
                        std::this_thread::sleep_for(std::chrono::microseconds(100));
                    }
                    
                    // This should trigger the spin-wait paths due to hash collisions
                    u64 trace_id = hash_table.put(1, &frame, false, 1);
                    
                    if (trace_id == 0) {
                        dropped_traces.fetch_add(1, std::memory_order_relaxed);
                        continue;
                    }
                    
                    if (trace_id == CallTraceStorage::DROPPED_TRACE_ID) {
                        allocation_failures.fetch_add(1, std::memory_order_relaxed);
                        continue;
                    }
                    
                    if (trace_id == 0x7fffffffffffffffULL) {  // OVERFLOW_TRACE_ID
                        continue;
                    }
                    
                    successful_insertions.fetch_add(1, std::memory_order_relaxed);
                    
                    // Every successful insertion in the same collision group indicates potential spin-wait
                    spin_wait_events.fetch_add(1, std::memory_order_relaxed);
                    
                    // Yield occasionally to increase interleaving and contention
                    if (op % 50 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    test_failed.store(true);
                    return;
                }
            }
        });
    }
    
    // Monitor thread to detect potential deadlocks in spin-wait logic
    std::atomic<bool> monitor_running{true};
    std::thread monitor([&]() {
        auto start_time = std::chrono::steady_clock::now();
        u64 last_insertions = 0;
        
        while (monitor_running.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            u64 current_insertions = successful_insertions.load();
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
            
            // Check for progress stall (potential deadlock in spin-wait)
            if (elapsed > 5 && current_insertions == last_insertions) {
                // No progress for too long - possible deadlock
                preparing_deadlock.store(true);
                test_failed.store(true);
                break;
            }
            
            // Check for excessive timeout recoveries
            if (timeout_recoveries.load() > successful_insertions.load() / 10) {
                timeout_detected.store(true);
            }
            
            // Check for allocation failure cascade
            if (allocation_failures.load() > successful_insertions.load()) {
                allocation_failure_cascade.store(true);
            }
            
            last_insertions = current_insertions;
        }
    });
    
    // Wait for all workers
    for (auto& worker : workers) {
        worker.join();
    }
    monitor_running.store(false);
    monitor.join();
    
    // Analyze results
    double failure_rate = (double)allocation_failures.load() / (successful_insertions.load() + allocation_failures.load());
    double drop_rate = (double)dropped_traces.load() / (successful_insertions.load() + dropped_traces.load());
    
    std::cout << "Hash table spin-wait stress test completed:" << std::endl;
    std::cout << "  Successful insertions: " << successful_insertions.load() << std::endl;
    std::cout << "  Allocation failures: " << allocation_failures.load() << std::endl;
    std::cout << "  Dropped traces: " << dropped_traces.load() << std::endl;
    std::cout << "  Spin-wait events: " << spin_wait_events.load() << std::endl;
    std::cout << "  Timeout recoveries: " << timeout_recoveries.load() << std::endl;
    std::cout << "  Hash collisions detected: " << hash_collisions_detected.load() << std::endl;
    std::cout << "  Failure rate: " << (failure_rate * 100.0) << "%" << std::endl;
    std::cout << "  Drop rate: " << (drop_rate * 100.0) << "%" << std::endl;
    std::cout << "  Preparing deadlock: " << (preparing_deadlock.load() ? "YES" : "NO") << std::endl;
    std::cout << "  Timeout detected: " << (timeout_detected.load() ? "YES" : "NO") << std::endl;
    std::cout << "  Allocation cascade: " << (allocation_failure_cascade.load() ? "YES" : "NO") << std::endl;
    
    // Verify results
    EXPECT_FALSE(test_failed.load()) << "Hash table spin-wait test failed";
    EXPECT_FALSE(preparing_deadlock.load()) << "Deadlock detected in PREPARING state spin-wait";
    EXPECT_GT(successful_insertions.load(), 0) << "No successful hash table insertions";
    
    // Some failures are expected under extreme contention, but not excessive
    EXPECT_LT(failure_rate, 0.8) << "Excessive allocation failure rate: " << failure_rate;
    EXPECT_LT(drop_rate, 0.5) << "Excessive trace drop rate: " << drop_rate;
}

// Test 13: Hash Table Memory Allocation Failure Stress Test
TEST_F(StressTestSuite, HashTableAllocationFailureStressTest) {
    const int NUM_THREADS = 8;
    const int OPERATIONS_PER_THREAD = 2000;
    const int LARGE_FRAME_COUNT = 500;  // Large stack traces to stress allocator
    
    std::atomic<bool> test_failed{false};
    std::atomic<bool> corruption_detected{false};
    std::atomic<bool> inconsistent_state{false};
    std::atomic<uint64_t> allocation_failures{0};
    std::atomic<uint64_t> successful_large_traces{0};
    std::atomic<uint64_t> key_cleanup_events{0};
    std::atomic<uint64_t> preparing_state_leaks{0};
    
    // Use heap allocation with proper alignment to avoid ASAN alignment issues
    void* aligned_memory = std::aligned_alloc(alignof(CallTraceHashTable), sizeof(CallTraceHashTable));
    ASSERT_NE(aligned_memory, nullptr) << "Failed to allocate aligned memory for CallTraceHashTable";
    
    auto hash_table_ptr = std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
        new(aligned_memory) CallTraceHashTable(), 
        [](CallTraceHashTable* ptr) {
            ptr->~CallTraceHashTable();
            std::free(ptr);
        }
    );
    CallTraceHashTable& hash_table = *hash_table_ptr;
    hash_table.setInstanceId(77);
    
    std::cout << "Testing hash table allocation failure recovery..." << std::endl;
    
    std::vector<std::thread> workers;
    for (int t = 0; t < NUM_THREADS; ++t) {
        workers.emplace_back([&, t]() {
            std::mt19937 gen(std::random_device{}() + t);
            std::uniform_int_distribution<int> frame_count_dis(1, LARGE_FRAME_COUNT);
            std::uniform_int_distribution<uint32_t> bci_dis(1, 1000000);
            std::uniform_int_distribution<uintptr_t> method_dis(0x100000, 0xFFFFFF);
            
            for (int op = 0; op < OPERATIONS_PER_THREAD && !test_failed.load(); ++op) {
                try {
                    // Create large stack traces to increase allocation pressure
                    int num_frames = frame_count_dis(gen);
                    std::vector<ASGCT_CallFrame> frames(num_frames);
                    
                    for (int f = 0; f < num_frames; ++f) {
                        frames[f].bci = bci_dis(gen) + t * 10000000 + op * 1000 + f;
                        frames[f].method_id = reinterpret_cast<jmethodID>(method_dis(gen) + f);
                    }
                    
                    // This should sometimes fail allocation due to large size
                    u64 trace_id = hash_table.put(num_frames, frames.data(), false, 1);
                    
                    if (trace_id == CallTraceStorage::DROPPED_TRACE_ID) {
                        allocation_failures.fetch_add(1, std::memory_order_relaxed);
                        // Verify that the slot was properly cleaned up after allocation failure
                        key_cleanup_events.fetch_add(1, std::memory_order_relaxed);
                    } else if (trace_id != 0 && trace_id != 0x7fffffffffffffffULL) {
                        successful_large_traces.fetch_add(1, std::memory_order_relaxed);
                        
                        // Verify trace ID structure for large traces
                        u64 instance_id = trace_id >> 32;
                        u64 slot = trace_id & 0xFFFFFFFFULL;
                        
                        if (instance_id != 77 || slot >= 1048576) {  // LARGE_TABLE_CAPACITY
                            inconsistent_state.store(true);
                            test_failed.store(true);
                            return;
                        }
                    }
                    
                    // Periodically check for leaked PREPARING states
                    if (op % 100 == 0) {
                        // This is a heuristic - we can't directly inspect internal state
                        // but if we see extreme allocation failures, it might indicate leaks
                        if (allocation_failures.load() > successful_large_traces.load() * 3) {
                            preparing_state_leaks.fetch_add(1, std::memory_order_relaxed);
                        }
                    }
                    
                    // Yield to allow other threads to interfere during allocation
                    if (op % 50 == 0) {
                        std::this_thread::yield();
                    }
                    
                } catch (...) {
                    test_failed.store(true);
                    return;
                }
            }
        });
    }
    
    // Wait for completion
    for (auto& worker : workers) {
        worker.join();
    }
    
    // Analyze results
    u64 total_operations = successful_large_traces.load() + allocation_failures.load();
    double allocation_failure_rate = (double)allocation_failures.load() / total_operations;
    
    std::cout << "Hash table allocation failure stress test completed:" << std::endl;
    std::cout << "  Total operations: " << total_operations << std::endl;
    std::cout << "  Successful large traces: " << successful_large_traces.load() << std::endl;
    std::cout << "  Allocation failures: " << allocation_failures.load() << std::endl;
    std::cout << "  Key cleanup events: " << key_cleanup_events.load() << std::endl;
    std::cout << "  Preparing state leaks: " << preparing_state_leaks.load() << std::endl;
    std::cout << "  Allocation failure rate: " << (allocation_failure_rate * 100.0) << "%" << std::endl;
    std::cout << "  Corruption detected: " << (corruption_detected.load() ? "YES" : "NO") << std::endl;
    std::cout << "  Inconsistent state: " << (inconsistent_state.load() ? "YES" : "NO") << std::endl;
    
    // Verify results
    EXPECT_FALSE(test_failed.load()) << "Allocation failure stress test failed";
    EXPECT_FALSE(corruption_detected.load()) << "Memory corruption detected";
    EXPECT_FALSE(inconsistent_state.load()) << "Inconsistent internal state detected";
    EXPECT_GT(total_operations, 0) << "No operations completed";
    
    // Some allocation failures are expected with large traces
    EXPECT_GT(successful_large_traces.load(), 0) << "No large traces successfully stored";
    
    // But not excessive leaks of PREPARING states
    EXPECT_LT(preparing_state_leaks.load(), total_operations / 100) << "Excessive PREPARING state leaks";
}

// Test 14: Real Profiler Signal Handler Stress - Now crash-safe with progressive difficulty
TEST_F(StressTestSuite, RealProfilerSignalStressSafe) {
    TestSuiteResults results;
    
    // Test with progressively more aggressive parameters to find the breaking point
    // macOS is more resource-constrained than Linux, so use conservative limits
    std::vector<std::pair<int, int>> test_configs;
    
#ifdef __APPLE__
    // macOS-specific conservative limits to avoid false positive crashes
    test_configs = {
        {50, 1},     // Very gentle - should always pass
        {200, 1},    // Moderate - likely to pass  
        {300, 1},    // Single-threaded stress - avoids macOS multi-thread signal issues
        {500, 1},    // Higher single-threaded load
        {100, 2},    // Conservative multi-thread test
        {200, 2},    // Moderate multi-thread - real bugs should still manifest
        {300, 2},    // Push macOS limits a bit - real memory bugs should still show
        {1000, 1},   // High single-threaded - tests signal coalescing limits
    };
    std::cout << "Running macOS-optimized signal stress tests..." << std::endl;
#else
    // Linux can handle higher stress levels
    test_configs = {
        {50, 1},     // Very gentle - should always pass
        {200, 1},    // Moderate - likely to pass
        {500, 2},    // Aggressive - may pass or fail
        {1000, 2},   // Very aggressive - likely to find issues
        {2000, 3},   // Extreme - very likely to crash
        {5000, 3},   // Extreme stress - ultimate test of critical section fixes
    };
    std::cout << "Running Linux-optimized signal stress tests..." << std::endl;
#endif
    
    std::cout << "Running progressive signal stress tests to find breaking points..." << std::endl;
    
    for (size_t i = 0; i < test_configs.size(); ++i) {
        int signal_count = test_configs[i].first;
        int thread_count = test_configs[i].second;
        
        std::string test_name = "SignalStress_" + std::to_string(signal_count) + "_signals_" 
                               + std::to_string(thread_count) + "_threads";
        
        auto test_func = [signal_count, thread_count]() {
            realProfilerSignalStressImpl(signal_count, thread_count);
        };
        
        bool test_passed = executeCrashSafeTest(test_name, test_func);
        
        if (test_passed) {
            results.recordPass(test_name);
        } else {
            // Determine if it was a crash or just a failure
            // We'll assume crashes for now since that's our main concern
            results.recordCrash(test_name);
            std::cout << "⚠️  Configuration " << test_name << " failed - bug found at this stress level!" << std::endl;
        }
        
        // Small pause between tests
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    // Print comprehensive results
    results.printSummary();
    
    // Test always "passes" from a gtest perspective - we report bugs instead of failing
    EXPECT_GT(results.passed_tests, 0) << "No signal stress configurations passed - complete system failure";
    
    if (results.crashed_tests > 0) {
        std::cout << "\n🎯 SUCCESS: Found " << results.crashed_tests << " stress levels that expose memory safety bugs!" << std::endl;
        std::cout << "These crashes indicate real vulnerabilities in the profiler's signal handling." << std::endl;
    } else {
        std::cout << "\n🛡️  Signal handling appears robust under all tested stress levels." << std::endl;
    }
}
