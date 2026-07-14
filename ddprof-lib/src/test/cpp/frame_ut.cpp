/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include <climits>
#include "../../main/cpp/frame.h"
#include "../../main/cpp/gtest_crash_handler.h"

// VMTestAccessor — friend of VM, lets tests toggle VM::isHotspot() since
// isRawPointer() now gates on it (raw pointers only exist on HotSpot).
class VMTestAccessor {
public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool v) { VM::_hotspot = v; }
};

static constexpr char FRAME_TEST_NAME[] = "FrameTest";

class GlobalSetup {
public:
    GlobalSetup() {
        installGtestCrashHandler<FRAME_TEST_NAME>();
    }
    ~GlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static GlobalSetup global_setup;

// ---- encode ----------------------------------------------------------------

TEST(FrameTypeEncodeTest, EncodedMarkerBitIsSet) {
    // Encoded values must have bit 20 set so decode can distinguish them from raw BCIs
    int encoded = FrameType::encode(FRAME_JIT_COMPILED, 0);
    EXPECT_NE(encoded & (1 << 20), 0) << "encode() must set the encoded-marker bit (bit 20)";
}

TEST(FrameTypeEncodeTest, EncodeStoresTypeInUpperBits) {
    // Type occupies bits [23:21], extracted by >> 21 & 7
    for (int t = FRAME_INTERPRETED; t <= FRAME_TYPE_MAX; ++t) {
        int encoded = FrameType::encode(t, 0);
        int extracted = (encoded >> 21) & 0x7;
        EXPECT_EQ(extracted, t) << "encode() must store type " << t << " in bits [23:21]";
    }
}

TEST(FrameTypeEncodeTest, EncodeBciStoredInLower16Bits) {
    int bci = 0x1234;
    int encoded = FrameType::encode(FRAME_INTERPRETED, bci);
    EXPECT_EQ(encoded & 0xffff, bci) << "encode() must store BCI in the lower 16 bits";
}

TEST(FrameTypeEncodeTest, EncodeBciMaskedTo16Bits) {
    // BCI is masked with 0xffff; overflow bits are silently dropped
    int encoded = FrameType::encode(FRAME_INTERPRETED, 0x1ffff);
    EXPECT_EQ(encoded & 0xffff, 0xffff)
        << "encode() must mask BCI to 16 bits (0xffff & 0x1ffff == 0xffff)";
}

TEST(FrameTypeEncodeTest, RawPointerBitNotSetByDefault) {
    int encoded = FrameType::encode(FRAME_JIT_COMPILED, 0);
    EXPECT_EQ(encoded & (1 << 30), 0) << "rawPointer flag (bit 30) must not be set by default";
}

TEST(FrameTypeEncodeTest, EncodedValuesArePositive) {
    for (int t = FRAME_INTERPRETED; t <= FRAME_TYPE_MAX; ++t) {
        int encoded = FrameType::encode(t, 0);
        EXPECT_GT(encoded, 0) << "encode() must return a positive value for type " << t;
    }
}

// ---- decode ----------------------------------------------------------------

TEST(FrameTypeDecodeTest, DecodeZeroReturnsJitCompiled) {
    EXPECT_EQ(FrameType::decode(0), FRAME_JIT_COMPILED)
        << "decode(0) must return FRAME_JIT_COMPILED (unencoded sentinel)";
}

TEST(FrameTypeDecodeTest, DecodeNegativeReturnsJitCompiled) {
    EXPECT_EQ(FrameType::decode(-1), FRAME_JIT_COMPILED);
    EXPECT_EQ(FrameType::decode(INT_MIN), FRAME_JIT_COMPILED);
    EXPECT_EQ(FrameType::decode(-100), FRAME_JIT_COMPILED);
}

TEST(FrameTypeDecodeTest, DecodeUnencodedPositiveReturnsJitCompiled) {
    // Values without the encoded-marker bit should be treated as raw BCIs
    EXPECT_EQ(FrameType::decode(1), FRAME_JIT_COMPILED);
    EXPECT_EQ(FrameType::decode(42), FRAME_JIT_COMPILED);
    int bci = (int)(unsigned short)(0xffff);
    EXPECT_EQ(FrameType::decode(bci), FRAME_JIT_COMPILED);
}

TEST(FrameTypeDecodeTest, RoundTripAllTypesZeroBci) {
    // encode then decode must recover the original type for every frame type.
    // BCI=0 exercises the common case (first bytecode instruction in a method).
    for (int t = FRAME_INTERPRETED; t <= FRAME_TYPE_MAX; ++t) {
        int encoded = FrameType::encode(t, 0);
        FrameTypeId decoded = FrameType::decode(encoded);
        EXPECT_EQ(decoded, static_cast<FrameTypeId>(t))
            << "Round-trip failed for type " << t << " with BCI=0"
            << " (encoded=0x" << std::hex << encoded << ")";
    }
}

TEST(FrameTypeDecodeTest, RoundTripAllTypesNonZeroBci) {
    // Spot-check several BCI values across the full [0, 0xffff] range
    const int bcis[] = {1, 4, 7, 16, 20, 100, 1000, 0x8000, 0xffff};
    for (int bci : bcis) {
        for (int t = FRAME_INTERPRETED; t <= FRAME_TYPE_MAX; ++t) {
            int encoded = FrameType::encode(t, bci);
            FrameTypeId decoded = FrameType::decode(encoded);
            EXPECT_EQ(decoded, static_cast<FrameTypeId>(t))
                << "Round-trip failed for type " << t << " BCI=" << bci
                << " (encoded=0x" << std::hex << encoded << ")";
        }
    }
}

TEST(FrameTypeDecodeTest, DecodedTypeIsInValidRange) {
    for (int t = FRAME_INTERPRETED; t <= FRAME_TYPE_MAX; ++t) {
        int encoded = FrameType::encode(t, 42);
        FrameTypeId decoded = FrameType::decode(encoded);
        EXPECT_GE(decoded, FRAME_INTERPRETED);
        EXPECT_LE(decoded, FRAME_TYPE_MAX);
    }
}

// ---- isRawPointer ----------------------------------------------------------

TEST(FrameTypeIsRawPointerTest, FalseForZero) {
    EXPECT_FALSE(FrameType::isRawPointer(0));
}

TEST(FrameTypeIsRawPointerTest, FalseForNegative) {
    EXPECT_FALSE(FrameType::isRawPointer(-1));
    EXPECT_FALSE(FrameType::isRawPointer(INT_MIN));
}

TEST(FrameTypeIsRawPointerTest, FalseForEncodedWithoutFlag) {
    // A normally-encoded value must not appear as a raw pointer
    for (int t = FRAME_INTERPRETED; t <= FRAME_TYPE_MAX; ++t) {
        int encoded = FrameType::encode(t, 0);
        EXPECT_FALSE(FrameType::isRawPointer(encoded))
            << "isRawPointer() must be false for encode(" << t << ", 0)";
    }
}

TEST(FrameTypeIsRawPointerTest, TrueWhenBit30IsSetOnHotspot) {
    // Manually set the raw-pointer flag (bit 30) on an encoded value.
    // Raw pointers only exist on HotSpot, so isRawPointer() must be gated on it.
    bool saved = VMTestAccessor::getHotspot();
    VMTestAccessor::setHotspot(true);
    int base = FrameType::encode(FRAME_JIT_COMPILED, 0);
    int withFlag = base | (1 << 30);
    EXPECT_TRUE(FrameType::isRawPointer(withFlag))
        << "isRawPointer() must be true when bit 30 is set, value is positive, and VM is HotSpot";
    VMTestAccessor::setHotspot(saved);
}

TEST(FrameTypeIsRawPointerTest, FalseWhenBit30IsSetOnNonHotspot) {
    // Non-HotSpot VMs can coincidentally produce an unencoded bci with bit 30
    // set (e.g. OpenJ9's raw AsyncGetCallTrace output); that must not be
    // mistaken for HotSpot's raw-pointer encoding.
    bool saved = VMTestAccessor::getHotspot();
    VMTestAccessor::setHotspot(false);
    int base = FrameType::encode(FRAME_JIT_COMPILED, 0);
    int withFlag = base | (1 << 30);
    EXPECT_FALSE(FrameType::isRawPointer(withFlag))
        << "isRawPointer() must be false when VM is not HotSpot, even with bit 30 set";
    VMTestAccessor::setHotspot(saved);
}

TEST(FrameTypeIsRawPointerTest, FalseWithOnlyBit30SetOnNegative) {
    // The function requires bci > 0, so a value with bit 30 set that is
    // interpreted as negative (bit 31 also set) must return false
    int negativeWithBit30 = static_cast<int>(0xC0000000u); // bits 31 and 30 set → negative
    EXPECT_LT(negativeWithBit30, 0);
    EXPECT_FALSE(FrameType::isRawPointer(negativeWithBit30));
}
