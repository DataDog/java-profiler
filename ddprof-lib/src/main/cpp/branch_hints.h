/*
 * Copyright 2025 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _BRANCH_HINTS_H
#define _BRANCH_HINTS_H

/**
 * Branch prediction hints for performance optimization.
 * 
 * These macros help the compiler generate more efficient code by providing
 * hints about which branches are more likely to be taken.
 * 
 * Usage:
 *   if (likely(common_condition)) { ... }
 *   if (unlikely(error_condition)) { ... }
 * 
 * Implementation:
 * - GCC/Clang: Uses __builtin_expect for branch prediction hints
 * - Other compilers: No-op (just returns the condition)
 */
// todo: in c++ 20, we can use [[likely]] and [[unlikely]]

#if defined(__GNUC__) || defined(__clang__)
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x)   (x)
#define unlikely(x) (x)
#endif

#endif // _BRANCH_HINTS_H 