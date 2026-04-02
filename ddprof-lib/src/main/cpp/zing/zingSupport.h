/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ZING_ZINGSUPPORT_H
#define _ZING_ZINGSUPPORT_H

#include <jvmti.h>
#include "stackWalker.h"

class ZingSupport {
public:
  static void* initialize(jthread thread);
};

#endif // _ZING_ZINGSUPPORT_H
