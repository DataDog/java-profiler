/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <array>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "profiler.h"
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

class ProfilerTestAccessor {
 public:
  static void setTaskBlockEnabled(Profiler* profiler, bool enabled) {
    profiler->setTaskBlockEnabled(enabled);
  }

  static void setTaskBlockState(Profiler* profiler, bool enabled,
                                bool monitor_events_enabled) {
    profiler->_task_block_enabled.store(enabled, std::memory_order_release);
    profiler->_task_block_monitor_events_enabled.store(
        monitor_events_enabled, std::memory_order_release);
  }

  static bool monitorEventsEnabled(Profiler* profiler) {
    return profiler->_task_block_monitor_events_enabled.load(
        std::memory_order_acquire);
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

class NativeMonitorEventsTest : public ::testing::Test {
 protected:
  struct EventCall {
    jvmtiEventMode mode;
    jvmtiEvent event;
    bool task_block_enabled;
  };

  static constexpr std::array<jvmtiEvent, 4> MONITOR_EVENTS = {
      JVMTI_EVENT_MONITOR_CONTENDED_ENTER,
      JVMTI_EVENT_MONITOR_CONTENDED_ENTERED,
      JVMTI_EVENT_MONITOR_WAIT,
      JVMTI_EVENT_MONITOR_WAITED,
  };

  inline static NativeMonitorEventsTest* active_test = nullptr;

  jvmtiInterface_1_ functions{};
  _jvmtiEnv mock_env{};
  std::vector<EventCall> calls;
  std::array<bool, MONITOR_EVENTS.size()> event_enabled{};
  bool inject_failure = false;
  bool fail_all_disables = false;
  jvmtiEventMode failure_mode = JVMTI_ENABLE;
  jvmtiEvent failure_event = JVMTI_EVENT_MONITOR_CONTENDED_ENTER;

  Profiler* profiler = Profiler::instance();
  jvmtiEnv* original_jvmti = nullptr;
  bool original_available = false;
  bool original_delegated = false;
  bool original_task_block_enabled = false;
  bool original_monitor_events_enabled = false;

  static jvmtiError JNICALL setEventNotificationMode(
      jvmtiEnv*, jvmtiEventMode mode, jvmtiEvent event, jthread, ...) {
    NativeMonitorEventsTest* test = active_test;
    test->calls.push_back(
        {mode, event, test->profiler->taskBlockEnabled()});
    if (test->inject_failure && mode == test->failure_mode &&
        event == test->failure_event) {
      return JVMTI_ERROR_INTERNAL;
    }
    if (test->fail_all_disables && mode == JVMTI_DISABLE) {
      return JVMTI_ERROR_INTERNAL;
    }

    test->event_enabled[test->eventIndex(event)] = mode == JVMTI_ENABLE;
    return JVMTI_ERROR_NONE;
  }

  void SetUp() override {
    original_jvmti = VMTestAccessor::jvmti();
    original_available = VMTestAccessor::nativeMonitorEventsAvailable();
    original_delegated = VMTestAccessor::monitorWaitEventsDelegated();
    original_task_block_enabled = profiler->taskBlockEnabled();
    original_monitor_events_enabled =
        ProfilerTestAccessor::monitorEventsEnabled(profiler);

    functions.SetEventNotificationMode = &setEventNotificationMode;
    mock_env.functions = &functions;
    VMTestAccessor::setJvmti(&mock_env);
    VMTestAccessor::setNativeMonitorEventsAvailable(true);
    VMTestAccessor::setMonitorWaitEventsDelegated(false);
    ProfilerTestAccessor::setTaskBlockState(profiler, false, false);
    active_test = this;
  }

  void TearDown() override {
    active_test = nullptr;
    ProfilerTestAccessor::setTaskBlockState(
        profiler, original_task_block_enabled, original_monitor_events_enabled);
    VMTestAccessor::setMonitorWaitEventsDelegated(original_delegated);
    VMTestAccessor::setNativeMonitorEventsAvailable(original_available);
    VMTestAccessor::setJvmti(original_jvmti);
  }

  static size_t eventIndex(jvmtiEvent event) {
    for (size_t i = 0; i < MONITOR_EVENTS.size(); i++) {
      if (MONITOR_EVENTS[i] == event) return i;
    }
    ADD_FAILURE() << "Unexpected JVMTI event " << event;
    return 0;
  }

  bool eventIsEnabled(jvmtiEvent event) const {
    return event_enabled[eventIndex(event)];
  }

  void setAllEventsEnabled(bool enabled) {
    event_enabled.fill(enabled);
  }

  void resetObservations() {
    calls.clear();
    event_enabled.fill(false);
    inject_failure = false;
    fail_all_disables = false;
  }

  void fail(jvmtiEventMode mode, jvmtiEvent event) {
    inject_failure = true;
    failure_mode = mode;
    failure_event = event;
  }

  void expectCalls(
      const std::vector<std::pair<jvmtiEventMode, jvmtiEvent>>& expected) {
    ASSERT_EQ(expected.size(), calls.size());
    for (size_t i = 0; i < expected.size(); i++) {
      EXPECT_EQ(expected[i].first, calls[i].mode) << "call " << i;
      EXPECT_EQ(expected[i].second, calls[i].event) << "call " << i;
    }
  }

  static std::vector<std::pair<jvmtiEventMode, jvmtiEvent>> disableCalls() {
    return {
        {JVMTI_DISABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTER},
        {JVMTI_DISABLE, JVMTI_EVENT_MONITOR_WAIT},
        {JVMTI_DISABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTERED},
        {JVMTI_DISABLE, JVMTI_EVENT_MONITOR_WAITED},
    };
  }
};

TEST_F(NativeMonitorEventsTest, EnablesTerminalEventsBeforeEntryEvents) {
  EXPECT_TRUE(VM::setNativeMonitorEventsEnabled(true));

  expectCalls({
      {JVMTI_ENABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTERED},
      {JVMTI_ENABLE, JVMTI_EVENT_MONITOR_WAITED},
      {JVMTI_ENABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTER},
      {JVMTI_ENABLE, JVMTI_EVENT_MONITOR_WAIT},
  });
  for (jvmtiEvent event : MONITOR_EVENTS) {
    EXPECT_TRUE(eventIsEnabled(event));
  }
}

TEST_F(NativeMonitorEventsTest, DelegatedEnableOnlyInstallsContendedPair) {
  VMTestAccessor::setMonitorWaitEventsDelegated(true);

  EXPECT_TRUE(VM::setNativeMonitorEventsEnabled(true));

  expectCalls({
      {JVMTI_ENABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTERED},
      {JVMTI_ENABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTER},
  });
  EXPECT_TRUE(eventIsEnabled(JVMTI_EVENT_MONITOR_CONTENDED_ENTER));
  EXPECT_TRUE(eventIsEnabled(JVMTI_EVENT_MONITOR_CONTENDED_ENTERED));
  EXPECT_FALSE(eventIsEnabled(JVMTI_EVENT_MONITOR_WAIT));
  EXPECT_FALSE(eventIsEnabled(JVMTI_EVENT_MONITOR_WAITED));
}

TEST_F(NativeMonitorEventsTest, DisableRemovesEntriesBeforeTerminalEvents) {
  for (bool delegated : {false, true}) {
    SCOPED_TRACE(delegated);
    resetObservations();
    setAllEventsEnabled(true);
    VMTestAccessor::setMonitorWaitEventsDelegated(delegated);

    EXPECT_TRUE(VM::setNativeMonitorEventsEnabled(false));

    expectCalls(disableCalls());
    for (jvmtiEvent event : MONITOR_EVENTS) {
      EXPECT_FALSE(eventIsEnabled(event));
    }
  }
}

TEST_F(NativeMonitorEventsTest, EnableFailureStopsAndRollsBackAllEvents) {
  const std::array<jvmtiEvent, 4> enable_order = {
      JVMTI_EVENT_MONITOR_CONTENDED_ENTERED,
      JVMTI_EVENT_MONITOR_WAITED,
      JVMTI_EVENT_MONITOR_CONTENDED_ENTER,
      JVMTI_EVENT_MONITOR_WAIT,
  };

  for (size_t failure_index = 0; failure_index < enable_order.size();
       failure_index++) {
    SCOPED_TRACE(failure_index);
    resetObservations();
    fail(JVMTI_ENABLE, enable_order[failure_index]);

    EXPECT_FALSE(VM::setNativeMonitorEventsEnabled(true));

    std::vector<std::pair<jvmtiEventMode, jvmtiEvent>> expected;
    for (size_t i = 0; i <= failure_index; i++) {
      expected.push_back({JVMTI_ENABLE, enable_order[i]});
    }
    std::vector<std::pair<jvmtiEventMode, jvmtiEvent>> rollback =
        disableCalls();
    expected.insert(expected.end(), rollback.begin(), rollback.end());
    expectCalls(expected);
    for (jvmtiEvent event : MONITOR_EVENTS) {
      EXPECT_FALSE(eventIsEnabled(event));
    }
  }
}

TEST_F(NativeMonitorEventsTest, DelegatedEnableFailureRollsBackAllEvents) {
  VMTestAccessor::setMonitorWaitEventsDelegated(true);
  const std::array<jvmtiEvent, 2> enable_order = {
      JVMTI_EVENT_MONITOR_CONTENDED_ENTERED,
      JVMTI_EVENT_MONITOR_CONTENDED_ENTER,
  };

  for (size_t failure_index = 0; failure_index < enable_order.size();
       failure_index++) {
    SCOPED_TRACE(failure_index);
    resetObservations();
    fail(JVMTI_ENABLE, enable_order[failure_index]);

    EXPECT_FALSE(VM::setNativeMonitorEventsEnabled(true));

    std::vector<std::pair<jvmtiEventMode, jvmtiEvent>> expected;
    for (size_t i = 0; i <= failure_index; i++) {
      expected.push_back({JVMTI_ENABLE, enable_order[i]});
    }
    std::vector<std::pair<jvmtiEventMode, jvmtiEvent>> rollback =
        disableCalls();
    expected.insert(expected.end(), rollback.begin(), rollback.end());
    expectCalls(expected);
    for (jvmtiEvent event : MONITOR_EVENTS) {
      EXPECT_FALSE(eventIsEnabled(event));
    }
  }
}

TEST_F(NativeMonitorEventsTest, DisableFailureStillAttemptsEveryEvent) {
  for (jvmtiEvent failed_event : MONITOR_EVENTS) {
    SCOPED_TRACE(failed_event);
    resetObservations();
    setAllEventsEnabled(true);
    fail(JVMTI_DISABLE, failed_event);

    EXPECT_FALSE(VM::setNativeMonitorEventsEnabled(false));

    expectCalls(disableCalls());
    for (jvmtiEvent event : MONITOR_EVENTS) {
      EXPECT_EQ(event == failed_event, eventIsEnabled(event));
    }
  }
}

TEST_F(NativeMonitorEventsTest, UnavailableCapabilityDoesNotCallJvmti) {
  VMTestAccessor::setNativeMonitorEventsAvailable(false);

  EXPECT_FALSE(VM::setNativeMonitorEventsEnabled(true));
  EXPECT_TRUE(calls.empty());
}

TEST_F(NativeMonitorEventsTest, AdmissionRemainsClosedDuringSuccessfulSetup) {
  ProfilerTestAccessor::setTaskBlockEnabled(profiler, true);

  ASSERT_FALSE(calls.empty());
  for (const EventCall& call : calls) {
    EXPECT_FALSE(call.task_block_enabled);
  }
  EXPECT_TRUE(profiler->taskBlockEnabled());
  EXPECT_TRUE(ProfilerTestAccessor::monitorEventsEnabled(profiler));
}

TEST_F(NativeMonitorEventsTest,
       AdmissionRemainsClosedDuringFailedSetupAndRollback) {
  fail(JVMTI_ENABLE, JVMTI_EVENT_MONITOR_WAIT);

  ProfilerTestAccessor::setTaskBlockEnabled(profiler, true);

  ASSERT_FALSE(calls.empty());
  for (const EventCall& call : calls) {
    EXPECT_FALSE(call.task_block_enabled);
  }
  EXPECT_TRUE(profiler->taskBlockEnabled());
  EXPECT_FALSE(ProfilerTestAccessor::monitorEventsEnabled(profiler));
  for (jvmtiEvent event : MONITOR_EVENTS) {
    EXPECT_FALSE(eventIsEnabled(event));
  }
}

TEST_F(NativeMonitorEventsTest,
       NativeAdmissionRemainsClosedWhenSetupAndRollbackFail) {
  fail(JVMTI_ENABLE, JVMTI_EVENT_MONITOR_WAIT);
  fail_all_disables = true;

  ProfilerTestAccessor::setTaskBlockEnabled(profiler, true);

  EXPECT_TRUE(profiler->taskBlockEnabled());
  EXPECT_FALSE(profiler->nativeMonitorTaskBlockEnabled());
  EXPECT_FALSE(ProfilerTestAccessor::monitorEventsEnabled(profiler));
  EXPECT_TRUE(eventIsEnabled(JVMTI_EVENT_MONITOR_CONTENDED_ENTER));
  EXPECT_TRUE(eventIsEnabled(JVMTI_EVENT_MONITOR_CONTENDED_ENTERED));
  EXPECT_FALSE(eventIsEnabled(JVMTI_EVENT_MONITOR_WAIT));
  EXPECT_TRUE(eventIsEnabled(JVMTI_EVENT_MONITOR_WAITED));
}

TEST_F(NativeMonitorEventsTest, AdmissionClosesBeforeNativeTeardown) {
  setAllEventsEnabled(true);
  ProfilerTestAccessor::setTaskBlockState(profiler, true, true);

  ProfilerTestAccessor::setTaskBlockEnabled(profiler, false);

  expectCalls(disableCalls());
  for (const EventCall& call : calls) {
    EXPECT_FALSE(call.task_block_enabled);
  }
  EXPECT_FALSE(profiler->taskBlockEnabled());
  EXPECT_FALSE(ProfilerTestAccessor::monitorEventsEnabled(profiler));
}
