/*
 * Copyright 2021 Andrei Pangin
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

#ifndef _J9WALLCLOCK_H
#define _J9WALLCLOCK_H

#include "wallclock/wallClock.h"

class J9WallClock : public BaseWallClock {
private:
  bool _sample_idle_threads;
  int _max_stack_depth;

  static void *threadEntry(void *wall_clock) {
    ((J9WallClock *)wall_clock)->timerLoop();
    return NULL;
  }

  void timerLoop() override;

public:
  const char *name() const override {
    return _sample_idle_threads ? "J9WallClock" : "J9Execution";
  }
  Mode mode() const override { return Mode::ASGCT; }

  inline void sampleIdleThreads() { _sample_idle_threads = true; }

  Error start(Arguments &args) override;
  void stop() override;
};

#endif // _J9WALLCLOCK_H
