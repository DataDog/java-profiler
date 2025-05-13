/*
 * Copyright 2021, 2023 Datadog, Inc
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

#pragma once
#include <string>

namespace RustDemangler {
constexpr size_t MAX_DEMANGLE_OUTPUT_SIZE = 4096;

bool is_probably_rust_legacy(const std::string &str);
std::string demangle(const std::string &str);
void append_checked(std::string &str, const std::string &append);

}; // namespace RustDemangler
