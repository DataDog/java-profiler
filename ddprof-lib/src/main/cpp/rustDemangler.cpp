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

#include "rustDemangler.h"

#include <array>

namespace RustDemangler {

// With some exceptions we don't handle here, v0 Rust symbols can end in a
// prefix followed by a 16-hexdigit hash, which must be removed
const std::string hash_pre = "::h";
const std::string hash_eg = "0123456789abcdef";

const std::array<std::pair<std::string, std::string>, 9> patterns = {{
    {"..", "::"},
    {"$C$", ","},
    {"$BP$", "*"},
    {"$GT$", ">"},
    {"$LT$", "<"},
    {"$LP$", "("},
    {"$RP$", ")"},
    {"$RF$", "&"},
    {"$SP$", "@"},
}};

inline bool is_hexdig(const char c) {
  return (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9');
}

// Simple conversion from hex digit to integer
inline int hex_to_int(char dig) {
  constexpr int k_a_hex_value = 0xa;
  if (dig >= '0' && dig <= '9') {
    return dig - '0';
  }
  if (dig >= 'a' && dig <= 'f') {
    return dig - 'a' + k_a_hex_value;
  }
  if (dig >= 'A' && dig <= 'F') {
    return dig - 'A' + k_a_hex_value;
  }
  return -1;
}

// Minimal check that a string can end, and does end, in a hashlike substring
inline bool has_hash(const std::string &str) {
  // If the size can't conform, then the string is invalid
  if (str.size() <= hash_pre.size() + hash_eg.size()) {
    return false;
  }

  // Check that the string contains the hash prefix in the right position
  if (str.compare(str.size() - hash_eg.size() - hash_pre.size(),
                  hash_pre.size(), hash_pre)) {
    return false;
  }

  // Check that the string ends in lowercase hex digits
  for (size_t i = str.size() - hash_eg.size(); i < str.size(); ++i) {
    if (!is_hexdig(str[i])) {
      return false;
    }
  }
  return true;
}

bool is_probably_rust_legacy(const std::string &str) {
  // Is the string too short to have a hash part in thefirst place?
  if (!has_hash(str)) {
    return false;
  }

  // Throw out `$$` and `$????$`, but not in-between
  const char *ptr = str.data();
  const char *end = ptr + str.size() - hash_pre.size() - hash_eg.size();
  for (; ptr <= end; ++ptr) {
    if (*ptr == '$') {
      if (ptr[1] == '$') {
        return false;
      }
      return ptr[2] == '$' || ptr[3] == '$' || ptr[4] == '$';
    }
    if (*ptr == '.') {
      return '.' != ptr[1] ||
             '.' != ptr[2]; // '.' and '..' are fine, '...' is not
    }
  }
  return true;
}

// Demangles a Rust string by building a copy piece-by-piece
std::string demangle(const std::string &str) {
  std::string ret;
  ret.reserve(str.size() - hash_eg.size() - hash_pre.size());

  size_t i = 0;

  // Special-case for repairing C++ demangling defect for Rust
  if (str[0] == '_' && str[1] == '$') {
    ++i;
  }

  for (; i < str.size() - hash_pre.size() - hash_eg.size(); ++i) {

    // Fast sieve for pattern-matching, since we know first chars
    if (str[i] == '.' || str[i] == '$') {
      bool replaced = false;

      // Try to replace one of the patterns
      for (const auto &pair : patterns) {
        const std::string &pattern = pair.first;
        const std::string &replacement = pair.second;
        if (!str.compare(i, pattern.size(), pattern)) {
          ret += replacement;
          i += pattern.size() - 1; // -1 because iterator inc
          replaced = true;
          break;
        }
      }

      // If we failed to replace, try a few failovers.  Notably, we recognize
      // that Rust may insert Unicode code points in the function name (other
      // implementations treat many individual points as patterns to search on)
      if (!replaced && str[i] == '.') {
        // Special-case for '.'
        ret += '-';
      } else if (!replaced && !str.compare(i, 2, "$u") && str[i + 4] == '$') {
        const size_t k_nb_read_chars = 5;
        const int hexa_base = 16;
        const int hi = hex_to_int(str[i + 2]);
        const int lo = hex_to_int(str[i + 3]);
        if (hi != -1 && lo != -1) {
          ret += static_cast<unsigned char>(lo + hexa_base * hi);
          i += k_nb_read_chars - 1; // - 1 because iterator inc
        } else {
          // We didn't have valid unicode values.  No further processing is
          // done, reinsert the `$u...$` sequence into the output string.
          ret += str.substr(i, k_nb_read_chars);
          i += k_nb_read_chars - 1; // -1 because iterator inc
        }
      } else if (!replaced) {
        ret += str[i];
      }
    } else {
      ret += str[i];
    }
  }

  return ret;
}
} // namespace RustDemangler
