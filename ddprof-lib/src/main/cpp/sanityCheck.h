/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SANITY_CHECK_H
#define _SANITY_CHECK_H

#include "arguments.h"

class SanityChecker {
  public:
    static Error runChecks(const Arguments& args);
};

#endif // _SANITY_CHECK_H
