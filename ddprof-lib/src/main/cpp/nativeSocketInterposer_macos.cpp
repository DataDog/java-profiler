/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __linux__

#include "nativeSocketInterposer.h"

NativeSocketInterposer* const NativeSocketInterposer::_instance = new NativeSocketInterposer();

#endif // !__linux__
