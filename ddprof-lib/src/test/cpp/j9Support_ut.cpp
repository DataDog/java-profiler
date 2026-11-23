/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "j9/j9Support.h"

// java.vm.version values reported by the Semeru builds on OpenJ9 0.60.0.
static const char *const SEMERU_0_60_VM_VERSIONS[] = {
    "1.8.0_502-b07-openj9-0.60.0", "11.0.32+9-openj9-0.60.0",
    "17.0.20+8-openj9-0.60.0",     "21.0.12+8-openj9-0.60.0",
    "25.0.4+7-openj9-0.60.0",      "26.0.2+10-openj9-0.60.0",
};

TEST(J9AsgctDeadlockProneVersion, semeruOn0_60IsProne) {
  for (const char *vm_version : SEMERU_0_60_VM_VERSIONS) {
    EXPECT_TRUE(J9Support::isAsgctDeadlockProneVersion(vm_version, nullptr))
        << vm_version;
  }
  EXPECT_TRUE(J9Support::isAsgctDeadlockProneVersion("openj9-0.60", nullptr));
}

TEST(J9AsgctDeadlockProneVersion, otherOpenJ9ReleasesAreNotProne) {
  const char *const versions[] = {
      "17.0.19+10-openj9-0.59.0", "11.0.32.1+1-openj9-0.61.0",
      "1.8.0_504-b01-openj9-0.61.0", "1.8.0_512-b09-openj9-0.63.0.1",
      "17.0.21.0.3+1-openj9-0.63.0", "openj9-0.601", "openj9-0.6",
      "2.9", "25.292-b10", "11.0.25+10", ""};
  for (const char *vm_version : versions) {
    EXPECT_FALSE(J9Support::isAsgctDeadlockProneVersion(vm_version, nullptr))
        << vm_version;
  }
}

TEST(J9AsgctDeadlockProneVersion, ibmSdk8FixPacks70To74AreProne) {
  EXPECT_TRUE(J9Support::isAsgctDeadlockProneVersion(
      "2.9", "pxa6480sr8fp70-20260702_01 (SR8 FP70)"));
  EXPECT_TRUE(J9Support::isAsgctDeadlockProneVersion(
      "2.9", "pxa6480sr8fp71-20260813_01 (SR8 FP71)"));
  EXPECT_TRUE(J9Support::isAsgctDeadlockProneVersion(nullptr, "(SR8 FP74)"));
}

TEST(J9AsgctDeadlockProneVersion, otherIbmSdk8FixPacksAreNotProne) {
  const char *const versions[] = {
      "pxa6480sr8fp75-20261105_01 (SR8 FP75)", "(SR8 FP69)", "(SR8 FP45)",
      "(SR8 FP7)", "(SR8 FP700)", "(SR8 FP)", "(SR8)", "(SR9 FP70)",
      "(SR7 FP70)", "pxa6480sr8fp70-20260702_01", "1.8.0_292-b10", ""};
  for (const char *runtime_version : versions) {
    EXPECT_FALSE(J9Support::isAsgctDeadlockProneVersion("2.9", runtime_version))
        << runtime_version;
  }
}

TEST(J9AsgctDeadlockProneVersion, nullInputsAreNotProne) {
  EXPECT_FALSE(J9Support::isAsgctDeadlockProneVersion(nullptr, nullptr));
}

TEST(J9AssessSamplers, deadlockRiskNeedsAsgctOnAProneJvm) {
  using C = J9SamplerChoice;
  EXPECT_TRUE(J9Support::assessSamplers(C::ASGCT, C::NONE, true).deadlock_risk);
  EXPECT_TRUE(J9Support::assessSamplers(C::NONE, C::ASGCT, true).deadlock_risk);
  EXPECT_TRUE(J9Support::assessSamplers(C::ASGCT, C::ASGCT, true).deadlock_risk);
  EXPECT_TRUE(
      J9Support::assessSamplers(C::ASGCT, C::JVMTI_REQUESTED, true).deadlock_risk);
  EXPECT_FALSE(J9Support::assessSamplers(C::ASGCT, C::ASGCT, false).deadlock_risk);
  const C non_asgct[] = {C::NONE, C::JVMTI_REQUESTED, C::JVMTI_GATED};
  for (C cpu : non_asgct) {
    for (C wall : non_asgct) {
      EXPECT_FALSE(J9Support::assessSamplers(cpu, wall, true).deadlock_risk)
          << J9Support::choiceName(cpu) << "/" << J9Support::choiceName(wall);
    }
  }
}

TEST(J9AssessSamplers, gatedFallbackOnlyForTheVersionGate) {
  using C = J9SamplerChoice;
  EXPECT_TRUE(
      J9Support::assessSamplers(C::JVMTI_GATED, C::NONE, false).gated_fallback);
  EXPECT_TRUE(
      J9Support::assessSamplers(C::NONE, C::JVMTI_GATED, false).gated_fallback);
  EXPECT_TRUE(
      J9Support::assessSamplers(C::JVMTI_GATED, C::ASGCT, true).gated_fallback);
  const C not_gated[] = {C::NONE, C::ASGCT, C::JVMTI_REQUESTED};
  for (C cpu : not_gated) {
    for (C wall : not_gated) {
      EXPECT_FALSE(J9Support::assessSamplers(cpu, wall, true).gated_fallback)
          << J9Support::choiceName(cpu) << "/" << J9Support::choiceName(wall);
    }
  }
}

TEST(J9AssessSamplers, choiceNamesAreDistinct) {
  EXPECT_STREQ("none", J9Support::choiceName(J9SamplerChoice::NONE));
  EXPECT_STREQ("asgct", J9Support::choiceName(J9SamplerChoice::ASGCT));
  EXPECT_STREQ("jvmti_requested",
               J9Support::choiceName(J9SamplerChoice::JVMTI_REQUESTED));
  EXPECT_STREQ("jvmti_gated", J9Support::choiceName(J9SamplerChoice::JVMTI_GATED));
}

TEST(J9ReportSamplerRisks, warnsAboutDeadlockOnlyWhenAsgctMeetsAProneBuild) {
  J9VersionProps prone = {"17.0.20+8-openj9-0.60.0", "17.0.20+8"};
  testing::internal::CaptureStderr();
  J9SamplerRisk risk = J9Support::reportSamplerRisks(
      J9SamplerChoice::ASGCT, J9SamplerChoice::JVMTI_REQUESTED, prone);
  std::string err = testing::internal::GetCapturedStderr();
  EXPECT_TRUE(risk.deadlock_risk);
  EXPECT_NE(std::string::npos, err.find("AsyncGetCallTrace can deadlock")) << err;
  EXPECT_NE(std::string::npos,
            err.find("java.vm.version=17.0.20+8-openj9-0.60.0")) << err;
  EXPECT_EQ(std::string::npos, err.find("using the JVMTI sampler")) << err;

  testing::internal::CaptureStderr();
  risk = J9Support::reportSamplerRisks(J9SamplerChoice::JVMTI_REQUESTED,
                                       J9SamplerChoice::JVMTI_REQUESTED, prone);
  err = testing::internal::GetCapturedStderr();
  EXPECT_FALSE(risk.deadlock_risk);
  EXPECT_TRUE(err.empty()) << err;
}

TEST(J9ReportSamplerRisks, namesUnreadPropertiesUnknown) {
  J9VersionProps ibm = {"", "pxa6480sr8fp70-20260702_01 (SR8 FP70)"};
  testing::internal::CaptureStderr();
  EXPECT_TRUE(J9Support::reportSamplerRisks(J9SamplerChoice::ASGCT,
                                            J9SamplerChoice::NONE, ibm)
                  .deadlock_risk);
  std::string err = testing::internal::GetCapturedStderr();
  EXPECT_NE(std::string::npos, err.find("java.vm.version=unknown")) << err;
}

TEST(J9ReportSamplerRisks, warnsAboutTheVersionGateOnly) {
  J9VersionProps fixed = {"17.0.21+1-openj9-0.63.0", "17.0.21+1"};
  testing::internal::CaptureStderr();
  J9SamplerRisk risk = J9Support::reportSamplerRisks(
      J9SamplerChoice::JVMTI_GATED, J9SamplerChoice::ASGCT, fixed);
  std::string err = testing::internal::GetCapturedStderr();
  EXPECT_FALSE(risk.deadlock_risk);
  EXPECT_TRUE(risk.gated_fallback);
  EXPECT_NE(std::string::npos, err.find("using the JVMTI sampler")) << err;
  EXPECT_EQ(std::string::npos, err.find("can deadlock")) << err;
}

TEST(J9ReportSamplerRisks, reportsBothRisksTogether) {
  J9VersionProps prone = {"21.0.12+8-openj9-0.60.0", "21.0.12+8"};
  testing::internal::CaptureStderr();
  J9SamplerRisk risk = J9Support::reportSamplerRisks(
      J9SamplerChoice::ASGCT, J9SamplerChoice::JVMTI_GATED, prone);
  std::string err = testing::internal::GetCapturedStderr();
  EXPECT_TRUE(risk.deadlock_risk);
  EXPECT_TRUE(risk.gated_fallback);
  EXPECT_NE(std::string::npos, err.find("AsyncGetCallTrace can deadlock")) << err;
  EXPECT_NE(std::string::npos, err.find("using the JVMTI sampler")) << err;
}

TEST(J9ReadVersionProps, nullEnvironmentsYieldEmptyValues) {
  J9VersionProps props = J9Support::readVersionProps(nullptr, nullptr);
  EXPECT_TRUE(props.vm_version.empty());
  EXPECT_TRUE(props.runtime_version.empty());
}
