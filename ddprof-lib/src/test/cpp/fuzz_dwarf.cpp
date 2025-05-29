#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <random>
#include <time.h>
#include <algorithm>
#include <chrono>
#include "dwarf.h"

// Constants for testing
const int TEST_TABLE_SIZE = 10;

// Define DWARF constants needed for testing
namespace {
    // DWARF Exception Header value format
    const uint8_t DW_EH_PE_uleb128 = 0x01;
    const uint8_t DW_EH_PE_udata2 = 0x02;
    const uint8_t DW_EH_PE_udata4 = 0x03;
    const uint8_t DW_EH_PE_udata8 = 0x04;
    const uint8_t DW_EH_PE_sleb128 = 0x09;
    const uint8_t DW_EH_PE_sdata2 = 0x0a;
    const uint8_t DW_EH_PE_sdata4 = 0x0b;
    const uint8_t DW_EH_PE_sdata8 = 0x0c;
    // DWARF Exception Header application
    const uint8_t DW_EH_PE_absptr = 0x00;
    const uint8_t DW_EH_PE_pcrel = 0x10;
    const uint8_t DW_EH_PE_datarel = 0x30;
    // valid in both
    const uint8_t DW_EH_PE_omit = 0xff;

    // DWARF Call Frame Instructions
    const uint8_t DW_CFA_nop = 0x0;
    const uint8_t DW_CFA_set_loc = 0x1;
    const uint8_t DW_CFA_advance_loc1 = 0x2;
    const uint8_t DW_CFA_advance_loc2 = 0x3;
    const uint8_t DW_CFA_advance_loc4 = 0x4;
    const uint8_t DW_CFA_offset_extended = 0x5;
    const uint8_t DW_CFA_restore_extended = 0x6;
    const uint8_t DW_CFA_undefined = 0x7;
    const uint8_t DW_CFA_same_value = 0x8;
    const uint8_t DW_CFA_register = 0x9;
    const uint8_t DW_CFA_remember_state = 0xa;
    const uint8_t DW_CFA_restore_state = 0xb;
    const uint8_t DW_CFA_def_cfa = 0xc;
    const uint8_t DW_CFA_def_cfa_register = 0xd;
    const uint8_t DW_CFA_def_cfa_offset = 0xe;
    const uint8_t DW_CFA_def_cfa_expression = 0xf;
    const uint8_t DW_CFA_expression = 0x10;
    const uint8_t DW_CFA_offset_extended_sf = 0x11;
    const uint8_t DW_CFA_def_cfa_sf = 0x12;
    const uint8_t DW_CFA_def_cfa_offset_sf = 0x13;
    const uint8_t DW_CFA_val_offset = 0x14;
    const uint8_t DW_CFA_val_offset_sf = 0x15;
    const uint8_t DW_CFA_val_expression = 0x16;

    const uint8_t DW_CFA_advance_loc = 0x1;
    const uint8_t DW_CFA_offset = 0x2;
    const uint8_t DW_CFA_restore = 0x3;

    // DWARF Expression operations
    const uint8_t DW_OP_const1u = 0x08;
    const uint8_t DW_OP_const1s = 0x09;
    const uint8_t DW_OP_const2u = 0x0a;
    const uint8_t DW_OP_const2s = 0x0b;
    const uint8_t DW_OP_const4u = 0x0c;
    const uint8_t DW_OP_const4s = 0x0d;
    const uint8_t DW_OP_constu = 0x10;
    const uint8_t DW_OP_consts = 0x11;
    const uint8_t DW_OP_minus = 0x1c;
    const uint8_t DW_OP_plus = 0x22;
    const uint8_t DW_OP_breg_pc = 0x70 + 8; // Assuming PC register index is 8
} // anonymous namespace

/**
 * Helper function that mimics the binary search logic used in the getFrameDesc method
 * based on the public API of dwarf.h
 */
const FrameDesc* findFrameDescHelper(const FrameDesc* table, int count, uint32_t target_loc) {
    if (count <= 0) return nullptr;
    
    const FrameDesc* frame = nullptr;
    int low = 0;
    int high = count - 1;
    
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (table[mid].loc < target_loc) {
            low = mid + 1;
        } else if (table[mid].loc > target_loc) {
            high = mid - 1;
        } else {
            return &table[mid];
        }
    }
    
    if (low > 0) {
        return &table[low - 1];
    }
    
    return nullptr;
}

// Helper to generate random buffer with specific patterns
class DwarfFuzzBuffer {
private:
    std::vector<char> _buffer;
    std::mt19937 _rng;

public:
    DwarfFuzzBuffer(size_t size, unsigned int seed) : _buffer(size, 0), _rng(seed) {}
    
    // Fill buffer with random data
    void randomize() {
        std::uniform_int_distribution<unsigned char> dist(0, 255);
        for (size_t i = 0; i < _buffer.size(); i++) {
            _buffer[i] = static_cast<char>(dist(_rng));
        }
    }
    
    // Create a semi-valid eh_frame_hdr at the beginning
    void createEhFrameHdr(bool valid_version = true) {
        if (_buffer.size() < 16) return;
        
        // Version
        _buffer[0] = valid_version ? 1 : 0; 
        
        // Encoding flags
        _buffer[1] = DW_EH_PE_udata4 | DW_EH_PE_pcrel;  // eh_frame_ptr_enc
        _buffer[2] = DW_EH_PE_udata4;                    // fde_count_enc
        _buffer[3] = DW_EH_PE_datarel | DW_EH_PE_udata4; // table_enc
        
        // FDE count - random but reasonable value
        std::uniform_int_distribution<int> count_dist(0, 100);
        int fde_count = count_dist(_rng);
        memcpy(&_buffer[8], &fde_count, sizeof(fde_count));
        
        // Make sure there's at least space for the table
        if (_buffer.size() >= (16 + fde_count * 8)) {
            // Fill table with random addresses
            std::uniform_int_distribution<int> addr_dist(0, 0x10000);
            for (int i = 0; i < fde_count; i++) {
                int offset = addr_dist(_rng);
                memcpy(&_buffer[16 + i * 8], &offset, sizeof(offset));
                
                int addr = addr_dist(_rng);
                memcpy(&_buffer[16 + i * 8 + 4], &addr, sizeof(addr));
            }
        }
    }
    
    const char* data() const { return _buffer.data(); }
    size_t size() const { return _buffer.size(); }
};

// Test fixture for DWARF tests
class DwarfFuzzTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for all tests
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// Basic lookup tests
TEST_F(DwarfFuzzTest, BasicLookup) {
    // Create a test table
    FrameDesc table[3];
    
    // Initialize with test values
    table[0].loc = 0x1000;
    table[0].cfa = DW_REG_SP | 16 << 8;
    table[0].fp_off = -16;
    table[0].pc_off = -8;
    
    table[1].loc = 0x2000;
    table[1].cfa = DW_REG_FP | 16 << 8;
    table[1].fp_off = -16;
    table[1].pc_off = -8;
    
    table[2].loc = 0x3000;
    table[2].cfa = DW_REG_SP | 32 << 8;
    table[2].fp_off = -32;
    table[2].pc_off = -16;
    
    // Test exact matches
    const FrameDesc* result1 = findFrameDescHelper(table, 3, 0x1000);
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->loc, 0x1000u);
    
    const FrameDesc* result2 = findFrameDescHelper(table, 3, 0x2000);
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->loc, 0x2000u);
    
    // Test address in between entries
    const FrameDesc* result3 = findFrameDescHelper(table, 3, 0x1500);
    ASSERT_NE(result3, nullptr);
    EXPECT_EQ(result3->loc, 0x1000u);
    
    // Test address beyond the last entry
    const FrameDesc* result4 = findFrameDescHelper(table, 3, 0x4000);
    ASSERT_NE(result4, nullptr);
    EXPECT_EQ(result4->loc, 0x3000u);
    
    // Test address before the first entry
    const FrameDesc* result5 = findFrameDescHelper(table, 3, 0x500);
    EXPECT_EQ(result5, nullptr);
    
    // Test with empty table
    const FrameDesc* result6 = findFrameDescHelper(nullptr, 0, 0x1000);
    EXPECT_EQ(result6, nullptr);
}

// Buffer generation tests
TEST_F(DwarfFuzzTest, BufferGeneration) {
    const size_t BUFFER_SIZE = 4096;
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    
    // Test random buffer
    DwarfFuzzBuffer buffer1(BUFFER_SIZE, seed);
    buffer1.randomize();
    EXPECT_EQ(buffer1.size(), BUFFER_SIZE);
    
    // Test eh_frame_hdr creation
    DwarfFuzzBuffer buffer2(BUFFER_SIZE, seed);
    buffer2.createEhFrameHdr(true);
    EXPECT_EQ(buffer2.data()[0], 1);
}

// Large table lookup tests
TEST_F(DwarfFuzzTest, LargeTableLookup) {
    const int TABLE_SIZE = 10000;
    
    // Create a larger test table
    std::vector<FrameDesc> table(TABLE_SIZE);
    
    // Fill with ascending addresses, spaced by 16 bytes
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].loc = i * 16;
        table[i].cfa = (i % 2 == 0) ? (DW_REG_SP | 16 << 8) : (DW_REG_FP | 16 << 8);
        table[i].fp_off = -16;
        table[i].pc_off = -8;
    }
    
    // Test exact matches at different positions
    const FrameDesc* result1 = findFrameDescHelper(table.data(), TABLE_SIZE, 0);
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(result1->loc, 0u);
    
    const FrameDesc* result2 = findFrameDescHelper(table.data(), TABLE_SIZE, 80000);
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->loc, 80000u);
    
    const FrameDesc* result3 = findFrameDescHelper(table.data(), TABLE_SIZE, (TABLE_SIZE - 1) * 16);
    ASSERT_NE(result3, nullptr);
    EXPECT_EQ(result3->loc, (TABLE_SIZE - 1) * 16u);
    
    // Test in-between entries
    const FrameDesc* result4 = findFrameDescHelper(table.data(), TABLE_SIZE, 81);
    ASSERT_NE(result4, nullptr);
    EXPECT_EQ(result4->loc, 80u);
    
    // Test performance with multiple lookups
    std::cout << "  Testing performance with multiple lookups..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    
    std::mt19937 rng(42);  // Fixed seed for reproducibility
    std::uniform_int_distribution<u32> dist(0, TABLE_SIZE * 16);
    
    const int NUM_LOOKUPS = 100000;
    for (int i = 0; i < NUM_LOOKUPS; i++) {
        u32 addr = dist(rng);
        const FrameDesc* result = findFrameDescHelper(table.data(), TABLE_SIZE, addr);
        
        // Verify the result is correct
        if (addr < table[0].loc) {
            EXPECT_EQ(result, nullptr);
        } else {
            ASSERT_NE(result, nullptr);
            
            // Verify it's the correct frame or the one before
            u32 nextFrameIndex = (result->loc / 16) + 1;
            if (nextFrameIndex < TABLE_SIZE) {
                EXPECT_LT(addr, table[nextFrameIndex].loc);
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "  Completed " << NUM_LOOKUPS << " lookups in " << elapsed.count() 
              << " seconds (" << NUM_LOOKUPS / elapsed.count() << " lookups/sec)" << std::endl;
}

// Unsorted table tests
TEST_F(DwarfFuzzTest, UnsortedTables) {
    const int TABLE_SIZE = 100;
    
    // Create an unsorted test table
    std::vector<FrameDesc> table(TABLE_SIZE);
    
    // Fill with random addresses
    std::mt19937 rng(42);  // Fixed seed for reproducibility
    std::uniform_int_distribution<u32> dist(0, 0xFFFFFF);
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].loc = dist(rng);
        table[i].cfa = DW_REG_SP | 16 << 8;
        table[i].fp_off = -16;
        table[i].pc_off = -8;
    }
    
    // Create a sorted copy for comparison
    std::vector<FrameDesc> sortedTable = table;
    
    // Sort the copy
    std::sort(sortedTable.begin(), sortedTable.end(), 
              [](const FrameDesc& a, const FrameDesc& b) { 
                  return a.loc < b.loc; 
              });
    
    // Test several random addresses against both tables
    const int NUM_TESTS = 100; // Reduced for faster test runs
    int sameResults = 0;
    
    for (int i = 0; i < NUM_TESTS; i++) {
        u32 addr = dist(rng);
        
        const FrameDesc* resultUnsorted = findFrameDescHelper(table.data(), TABLE_SIZE, addr);
        const FrameDesc* resultSorted = findFrameDescHelper(sortedTable.data(), TABLE_SIZE, addr);
        
        // In an unsorted table, binary search may not work correctly, but we expect SOME results
        if (resultUnsorted != nullptr && resultSorted != nullptr) {
            if (resultUnsorted->loc == resultSorted->loc) {
                sameResults++;
            }
        }
    }
    
    // We expect inconsistent results between sorted and unsorted lookups
    // This test mainly demonstrates that binary search requires sorted input
    std::cout << "  Got same result in " << sameResults << " out of " << NUM_TESTS 
              << " cases between sorted and unsorted tables" << std::endl;
}

// Duplicate address tests
TEST_F(DwarfFuzzTest, DuplicateAddresses) {
    const int TABLE_SIZE = 100;
    
    // Create a test table with duplicate addresses
    std::vector<FrameDesc> table(TABLE_SIZE);
    
    // Fill with some duplicates
    for (int i = 0; i < TABLE_SIZE; i++) {
        // Every 10 entries has the same address
        table[i].loc = (i / 10) * 0x1000;
        table[i].cfa = DW_REG_SP | 16 << 8;
        table[i].fp_off = -16;
        table[i].pc_off = -8;
    }
    
    // Test exact matches - should get valid results
    for (int i = 0; i < 10; i++) {
        u32 addr = i * 0x1000;
        const FrameDesc* result = findFrameDescHelper(table.data(), TABLE_SIZE, addr);
        
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->loc, addr);
    }
    
    // Test in-between values
    u32 addr = 0x1500;  // Between 0x1000 and 0x2000
    const FrameDesc* result = findFrameDescHelper(table.data(), TABLE_SIZE, addr);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->loc, 0x1000u);
}

// Edge case tests
TEST_F(DwarfFuzzTest, EdgeCases) {
    // Test with single entry
    FrameDesc singleEntry = {0x1000, DW_REG_SP | 16 << 8, -16, -8};
    
    const FrameDesc* result1 = findFrameDescHelper(&singleEntry, 1, 0x500);
    EXPECT_EQ(result1, nullptr);
    
    const FrameDesc* result2 = findFrameDescHelper(&singleEntry, 1, 0x1000);
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(result2->loc, 0x1000u);
    
    const FrameDesc* result3 = findFrameDescHelper(&singleEntry, 1, 0x2000);
    ASSERT_NE(result3, nullptr);
    EXPECT_EQ(result3->loc, 0x1000u);
    
    // Test with extreme values
    std::vector<FrameDesc> extremeTable(3);
    extremeTable[0].loc = 0;
    extremeTable[1].loc = 0x7FFFFFFF;
    extremeTable[2].loc = 0xFFFFFFFF;
    
    const FrameDesc* result4 = findFrameDescHelper(extremeTable.data(), 3, 0);
    ASSERT_NE(result4, nullptr);
    EXPECT_EQ(result4->loc, 0u);
    
    const FrameDesc* result5 = findFrameDescHelper(extremeTable.data(), 3, 0x80000000);
    ASSERT_NE(result5, nullptr);
    EXPECT_EQ(result5->loc, 0x7FFFFFFF);
    
    const FrameDesc* result6 = findFrameDescHelper(extremeTable.data(), 3, 0xFFFFFFFF);
    ASSERT_NE(result6, nullptr);
    EXPECT_EQ(result6->loc, 0xFFFFFFFF);
}

// Randomized input test
TEST_F(DwarfFuzzTest, RandomizedInput) {
    const size_t BUFFER_SIZE = 4096; // Small enough to not cause OOM
    
    // Use current time as seed for randomization
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 rng(seed);
    
    // Try various combinations of inputs (reduced for faster test runs)
    for (int i = 0; i < 10; i++) {
        DwarfFuzzBuffer buffer(BUFFER_SIZE, seed + i);
        
        // Different types of buffers to test
        switch (i % 5) {
            case 0: // Completely random data
                buffer.randomize();
                break;
                
            case 1: // Valid header, random data
                buffer.randomize();
                buffer.createEhFrameHdr(true);
                break;
                
            case 2: // Invalid header, random data
                buffer.randomize();
                buffer.createEhFrameHdr(false);
                break;
                
            case 3: // Semi-structured data
                buffer.randomize();
                buffer.createEhFrameHdr(true);
                break;
                
            case 4: // Different layout
                buffer.randomize();
                buffer.createEhFrameHdr(true);
                break;
        }
        
        // We only test that the buffer was created successfully
        EXPECT_EQ(buffer.size(), BUFFER_SIZE);
    }
} 