#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../../main/cpp/flightRecorder.h"


class MethodInfoHashTest : public ::testing::Test {
};

TEST_F(MethodInfoHashTest, makeHashTest) {
    unsigned long dummy = 0xABCD1234;
    // jmethodID key
    unsigned long key1 = MethodMap::makeKey((jmethodID)dummy);
    // method name address key
    unsigned long key2 = MethodMap::makeKey((const char*)dummy);
    // packed remote frame key
    unsigned long key3 = MethodMap::makeKey((unsigned long)dummy);

    // The same value of different types should produce different keys
    EXPECT_TRUE(key1 != key2);
    EXPECT_TRUE(key1 != key3);
    EXPECT_TRUE(key2 != key3);
}
