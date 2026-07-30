/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "vmEntry.h"

class VMTestAccessor {
 public:
  static jvmtiEnv* jvmti() { return VM::_jvmti; }
  static void setJvmti(jvmtiEnv* jvmti) { VM::_jvmti = jvmti; }

  static bool nativeMonitorEventsAvailable() {
    return VM::_native_monitor_events_available;
  }
  static void setNativeMonitorEventsAvailable(bool available) {
    VM::_native_monitor_events_available = available;
  }

  static bool monitorWaitEventsDelegated() {
    return VM::_monitor_wait_events_delegated;
  }
  static void setMonitorWaitEventsDelegated(bool delegated) {
    VM::_monitor_wait_events_delegated = delegated;
  }

  static bool profilerBridgeInitialized() {
    return VM::_profiler_bridge_initialized;
  }
  static void setProfilerBridgeInitialized(bool initialized) {
    VM::_profiler_bridge_initialized = initialized;
  }

  static void configureMonitorEvents(bool delegate_monitor_wait_events) {
    VM::configureMonitorEvents(delegate_monitor_wait_events);
  }
};

class MonitorEventConfigurationTest : public ::testing::Test {
 protected:
  inline static MonitorEventConfigurationTest* active_test = nullptr;

  jvmtiInterface_1_ functions{};
  _jvmtiEnv mock_env{};
  jvmtiEnv* original_jvmti = nullptr;
  bool original_initialized = false;
  bool original_available = false;
  bool original_delegated = false;
  bool capability_available = false;
  int get_capabilities_calls = 0;

  static jvmtiError JNICALL getCapabilities(
      jvmtiEnv*, jvmtiCapabilities* capabilities) {
    MonitorEventConfigurationTest* test = active_test;
    *capabilities = jvmtiCapabilities{};
    capabilities->can_generate_monitor_events = test->capability_available;
    test->get_capabilities_calls++;
    return JVMTI_ERROR_NONE;
  }

  void SetUp() override {
    original_jvmti = VMTestAccessor::jvmti();
    original_initialized = VMTestAccessor::profilerBridgeInitialized();
    original_available = VMTestAccessor::nativeMonitorEventsAvailable();
    original_delegated = VMTestAccessor::monitorWaitEventsDelegated();

    functions.GetCapabilities = &getCapabilities;
    mock_env.functions = &functions;
    VMTestAccessor::setJvmti(&mock_env);
    VMTestAccessor::setProfilerBridgeInitialized(false);
    active_test = this;
  }

  void TearDown() override {
    active_test = nullptr;
    VMTestAccessor::setMonitorWaitEventsDelegated(original_delegated);
    VMTestAccessor::setNativeMonitorEventsAvailable(original_available);
    VMTestAccessor::setProfilerBridgeInitialized(original_initialized);
    VMTestAccessor::setJvmti(original_jvmti);
  }
};

TEST_F(MonitorEventConfigurationTest,
       StoresRequestedOwnershipIndependentlyOfCapability) {
  for (bool available : {false, true}) {
    for (bool delegated : {false, true}) {
      SCOPED_TRACE(::testing::Message()
                   << "available=" << available
                   << ", delegated=" << delegated);
      capability_available = available;
      get_capabilities_calls = 0;

      VMTestAccessor::configureMonitorEvents(delegated);

      EXPECT_EQ(1, get_capabilities_calls);
      EXPECT_EQ(available, VMTestAccessor::nativeMonitorEventsAvailable());
      EXPECT_EQ(delegated, VMTestAccessor::monitorWaitEventsDelegated());
      EXPECT_FALSE(VMTestAccessor::profilerBridgeInitialized());
    }
  }
}

class ProfilerBridgeDelegationTest : public ::testing::Test {
 protected:
  bool original_initialized = false;
  bool original_available = false;
  bool original_delegated = false;

  void SetUp() override {
    original_initialized = VMTestAccessor::profilerBridgeInitialized();
    original_available = VMTestAccessor::nativeMonitorEventsAvailable();
    original_delegated = VMTestAccessor::monitorWaitEventsDelegated();
    VMTestAccessor::setProfilerBridgeInitialized(true);
  }

  void TearDown() override {
    VMTestAccessor::setMonitorWaitEventsDelegated(original_delegated);
    VMTestAccessor::setNativeMonitorEventsAvailable(original_available);
    VMTestAccessor::setProfilerBridgeInitialized(original_initialized);
  }

  static void expectNegotiation(bool available, bool delegated,
                                bool requested,
                                ProfilerBridgeInitResult expected) {
    VMTestAccessor::setNativeMonitorEventsAvailable(available);
    VMTestAccessor::setMonitorWaitEventsDelegated(delegated);

    EXPECT_EQ(expected, VM::initProfilerBridge(nullptr, true, requested));
    EXPECT_TRUE(VMTestAccessor::profilerBridgeInitialized());
    EXPECT_EQ(available, VMTestAccessor::nativeMonitorEventsAvailable());
    EXPECT_EQ(delegated, VMTestAccessor::monitorWaitEventsDelegated());
  }
};

TEST_F(ProfilerBridgeDelegationTest,
       ReusesMatchingOwnershipWhenCapabilityIsUnavailable) {
  expectNegotiation(false, false, false, ProfilerBridgeInitResult::SUCCESS);
  expectNegotiation(false, true, true, ProfilerBridgeInitResult::SUCCESS);
}

TEST_F(ProfilerBridgeDelegationTest,
       RejectsConflictingOwnershipWhenCapabilityIsUnavailable) {
  expectNegotiation(
      false, false, true,
      ProfilerBridgeInitResult::MONITOR_EVENTS_DELEGATION_CONFLICT);
  expectNegotiation(
      false, true, false,
      ProfilerBridgeInitResult::MONITOR_EVENTS_DELEGATION_CONFLICT);
}

TEST_F(ProfilerBridgeDelegationTest,
       ReusesMatchingOwnershipWhenCapabilityIsAvailable) {
  expectNegotiation(true, false, false, ProfilerBridgeInitResult::SUCCESS);
  expectNegotiation(true, true, true, ProfilerBridgeInitResult::SUCCESS);
}

TEST_F(ProfilerBridgeDelegationTest,
       RejectsConflictingOwnershipWhenCapabilityIsAvailable) {
  expectNegotiation(
      true, false, true,
      ProfilerBridgeInitResult::MONITOR_EVENTS_DELEGATION_CONFLICT);
  expectNegotiation(
      true, true, false,
      ProfilerBridgeInitResult::MONITOR_EVENTS_DELEGATION_CONFLICT);
}
