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
#include <math.h>
#include <vector>


template <class T>
class ReservoirSampler {
private:
    // Algorithm L needs log() of the draw and log(1 - weight) to stay finite,
    // which xorshift::toUnitDouble already ensures by excluding both 0 and 1.
    // This floor is not about finiteness: it reproduces the lower bound the
    // sampler has always drawn from, so the jump distribution is unchanged.
    // Without it draws reach ~2.7e-20 instead of 1e-16, lengthening the tail of
    // skipped elements.
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