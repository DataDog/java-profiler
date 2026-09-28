/*
 * Copyright 2024 Datadog
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

#ifndef RESERVOIR_SAMPLER_H
#define RESERVOIR_SAMPLER_H

#include "xorshift.h"
#include <cassert>
#include <math.h>
#include <vector>


template <class T>
class ReservoirSampler {
private:
    // Keep the draw far enough above 0 that `1 - weight` stays distinguishable
    // from 1.0. This matters at _size == 1 (reachable via
    // wall_threads_per_tick=1), where weight == the draw: a draw of ~2.7e-20 --
    // toUnitDouble's smallest -- makes `1 - weight` round to exactly 1.0,
    // log(1 - weight) exactly 0.0, and the division below -inf, whose cast to
    // int is undefined. 1e-16 is above 2^-53, so `1 - weight` stays below 1.0.
    //
    // A draw that low has probability ~1e-16, so this never fires in practice
    // and cannot reasonably be tested -- but it is the difference between a
    // defined result and undefined behaviour, so it is not dead code. It also
    // reproduces the lower bound of the uniform_real_distribution(1e-16, 1.0)
    // the sampler drew from previously.
    static constexpr double MIN_UNIFORM = 1e-16;

    const int _size;
    u64 _rng;
    std::vector<T> _reservoir;

    double nextUniform() {
        double u = xorshift::toUnitDouble(xorshift::next(_rng));
        return u < MIN_UNIFORM ? MIN_UNIFORM : u;
    }

public:
    /**
     * @param size   reservoir capacity
     * @param stream distinguishes this sampler's random stream from others'.
     *               The instance address alone is not enough: successive
     *               samplers built at one call site reuse the same address and
     *               would replay the same stream, so callers pass something
     *               that varies between them (a tick count, say).
     */
    ReservoirSampler(const int size, u64 stream) :
        _size(size),
        _rng(xorshift::seed((u64)(uintptr_t)this, stream)) {
        _reservoir.reserve(size);
    }

    std::vector<T>& sample(const std::vector<T> &input) {
        _reservoir.clear();
        for (int i = 0; i < _size && i < (int)input.size(); i++) {
            _reservoir.push_back(input[i]);
        }
        double weight = exp(log(nextUniform()) / _size);
        int target = _size + (int) (log(nextUniform()) / log(1 - weight));
        assert(target >= 0);
        while (target < (int)input.size()) {
            _reservoir[xorshift::boundedIndex(xorshift::next(_rng), (u32)_size)] = input[target];
            weight *= exp(log(nextUniform()) / _size);
            target += (int) (log(nextUniform()) / log(1 - weight));
        }
        return _reservoir;
    }
};

#endif //RESERVOIR_SAMPLER_H