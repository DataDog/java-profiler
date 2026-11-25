/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SAMPLERCHOICE_H
#define _SAMPLERCHOICE_H

/** Why engine selection did or did not pick AsyncGetCallTrace for a sampler. */
enum class SamplerChoice : int {
  NONE,             // sampler off, or no ASGCT gate applies on this JVM
  ASGCT,
  JVMTI_REQUESTED,  // the user configured the JVMTI sampler
  JVMTI_GATED       // a JVM version gate rejected ASGCT
};

inline const char *samplerChoiceName(SamplerChoice choice) {
  switch (choice) {
  case SamplerChoice::NONE:
    return "none";
  case SamplerChoice::ASGCT:
    return "asgct";
  case SamplerChoice::JVMTI_REQUESTED:
    return "jvmti_requested";
  case SamplerChoice::JVMTI_GATED:
    return "jvmti_gated";
  }
  return "unknown";
}

#endif // _SAMPLERCHOICE_H
