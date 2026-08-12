/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/flightRecorder.h"
#include "../../main/cpp/hotspot/hotspotSupport.h"
#include "../../main/cpp/hotspot/vmStructs.h"

// Test-only friend accessor for VM internals. It exists solely so this test
// can exercise HotSpot's rejected-jmethodID handling.
class VMTestAccessor {
public:
    static bool getHotspot() { return VM::_hotspot; }
    static void setHotspot(bool value) { VM::_hotspot = value; }
};

class HotspotMethodIdVMHotspotGuard {
private:
    bool _saved;

public:
    HotspotMethodIdVMHotspotGuard() : _saved(VMTestAccessor::getHotspot()) {
        VMTestAccessor::setHotspot(true);
    }

    ~HotspotMethodIdVMHotspotGuard() {
        VMTestAccessor::setHotspot(_saved);
    }
};

TEST(HotspotMethodIdTest, RejectedMethodIdStaysNonRawAndResolvesToUnknown) {
    HotspotMethodIdVMHotspotGuard hotspot;
    ASGCT_CallFrame frame{};

    // The pointer is intentionally invalid. A rejected jmethodID must retain
    // only its sentinel and must not preserve this Method* for dump-time use.
    HotspotSupport::fillJavaFrame(frame, FRAME_JIT_COMPILED, 17,
                                  JMETHODID_NOT_WALKABLE,
                                  reinterpret_cast<VMMethod*>(1));

    EXPECT_FALSE(FrameType::isRawPointer(frame.bci));
    EXPECT_EQ(frame.method_id, JMETHODID_NOT_WALKABLE);

    StringDictionary classes;
    MethodMap methods;
    Lookup lookup(nullptr, &methods, &classes);
    MethodInfo* info = lookup.resolveMethod(frame);

    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->_type, FRAME_NATIVE);
    // The sentinel is normalised to a null method_id, which resolves to the
    // shared unknown row. That row lives outside the MethodMap (see
    // Lookup::_unknown_method), so nothing is inserted for this frame.
    EXPECT_EQ(info, &lookup._unknown_method);
    EXPECT_TRUE(methods.empty());
    EXPECT_NE(info->_key, 0U);  // still needs a pool id to be referenceable
}
