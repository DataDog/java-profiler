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
    const int size;
    std::mt19937 generator;
    std::uniform_real_distribution<double> uniform;
    std::uniform_int_distribution<int> random_index;
    std::vector<T> reservoir;

public:
    ReservoirSampler(const int size) :
        size(size),
        generator([]() {
            std::random_device rd;
            std::seed_seq seed_seq{rd(), rd(), rd(), rd()};
            return std::mt19937(seed_seq);
        }()),
        uniform(1e-16, 1.0),
        random_index(0, size - 1) {
        reservoir.reserve(size);
    }

    std::vector<T>& sample(const std::vector<T> &input) {
        reservoir.clear();
        for (int i = 0; i < size && i < input.size(); i++) {
            reservoir.push_back(input[i]);
        }
        double weight = exp(log(uniform(generator)) / size);
        int target = size + (int) (log(uniform(generator)) / log(1 - weight));
        while (target < input.size()) {
            reservoir[random_index(generator)] = input[target];
            weight *= exp(log(uniform(generator)) / size);
            target += (int) (log(uniform(generator)) / log(1 - weight));
        }
        return reservoir;
    }
};

#endif //RESERVOIR_SAMPLER_H