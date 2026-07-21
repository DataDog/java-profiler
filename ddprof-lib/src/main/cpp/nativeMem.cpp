/*
 * Copyright 2026 Datadog, Inc
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
#include "nativeMem.h"

volatile long long NativeMem::_live[NM_NUM_CATEGORIES] = {};
volatile long long NativeMem::_max[NM_NUM_CATEGORIES] = {};
long long NativeMem::_window[NM_NUM_CATEGORIES][NativeMem::WINDOW] = {};
long long NativeMem::_total_window[NativeMem::WINDOW] = {};
int NativeMem::_window_pos = 0;
int NativeMem::_window_count = 0;
long long NativeMem::_avg[NM_NUM_CATEGORIES] = {};
long long NativeMem::_total_avg = 0;
long long NativeMem::_total_max_observed = 0;

long long NativeMem::liveTotal() {
  long long total = 0;
  for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
    total += load(_live[c]);
  }
  return total;
}

long long NativeMem::maxTotal() {
  long long total = 0;
  for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
    total += load(_max[c]);
  }
  return total;
}

void NativeMem::sample() {
  long long total = 0;
  for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
    long long v = load(_live[c]);
    // A category's live bytes are never negative under correct pairing (asserted
    // in record()). This clamp is a release-mode safety net: should an accounting
    // bug slip past the assert under NDEBUG, it keeps a negative from skewing the
    // window average and total rather than propagating garbage.
    if (v < 0) {
      v = 0;
    }
    _window[c][_window_pos] = v;
    total += v;
  }

  // The per-category peaks are maintained precisely at allocation time by
  // record(); here we only track the observed total (lower bound on the peak).
  _total_window[_window_pos] = total;
  if (total > _total_max_observed) {
    _total_max_observed = total;
  }

  _window_pos = (_window_pos + 1) % WINDOW;
  if (_window_count < WINDOW) {
    _window_count++;
  }

  for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
    long long sum = 0;
    for (int i = 0; i < _window_count; i++) {
      sum += _window[c][i];
    }
    _avg[c] = sum / _window_count;
  }

  long long total_sum = 0;
  for (int i = 0; i < _window_count; i++) {
    total_sum += _total_window[i];
  }
  _total_avg = total_sum / _window_count;
}

void NativeMem::reset() {
  for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
    store(_live[c], (long long)0);
    store(_max[c], (long long)0);
    _avg[c] = 0;
    for (int i = 0; i < WINDOW; i++) {
      _window[c][i] = 0;
    }
  }
  for (int i = 0; i < WINDOW; i++) {
    _total_window[i] = 0;
  }
  _window_pos = 0;
  _window_count = 0;
  _total_avg = 0;
  _total_max_observed = 0;
}

const char *NativeMem::categoryName(NativeMemCategory category) {
#define X_NM_NAME(a, b) b,
  static const char *const names[] = {DD_NATIVE_MEM_CATEGORY_TABLE(X_NM_NAME)};
#undef X_NM_NAME
  if (category < 0 || category >= NM_NUM_CATEGORIES) {
    return "unknown";
  }
  return names[category];
}
