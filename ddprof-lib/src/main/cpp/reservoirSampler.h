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

#include <math.h>
#include <random>
#include <vector>


template <class T>
class ReservoirSampler {
private:
    const int _size;
    std::mt19937 _generator;
    std::uniform_real_distribution<double> _uniform;
    std::uniform_int_distribution<int> _random_index;
    std::vector<T> _reservoir;

public:
    ReservoirSampler(const int size) :
        _size(size),
        _generator([]() {
            std::random_device rd;
            std::seed_seq seed_seq{rd(), rd(), rd(), rd()};
            return std::mt19937(seed_seq);
        }()),
        _uniform(1e-16, 1.0),
        _random_index(0, size - 1) {
        _reservoir.reserve(size);
    }

    std::vector<T>& sample(const std::vector<T> &input) {
        _reservoir.clear();
        for (int i = 0; i < _size && i < input.size(); i++) {
            _reservoir.push_back(input[i]);
        }
        double weight = exp(log(_uniform(_generator)) / _size);
        int target = _size + (int) (log(_uniform(_generator)) / log(1 - weight));
        while (target < input.size()) {
            _reservoir[_random_index(_generator)] = input[target];
            weight *= exp(log(_uniform(_generator)) / _size);
            target += (int) (log(_uniform(_generator)) / log(1 - weight));
        }
        return _reservoir;
    }
};

#endif //RESERVOIR_SAMPLER_H