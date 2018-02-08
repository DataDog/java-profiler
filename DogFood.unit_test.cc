#include "DogFood.h"

int main() {
    const auto tags = DogFood::Tags({{"d", "1"}, {"e", "2"}});
    auto i = DogFood::Metric("DogFoodTest", 69.523456236, DogFood::Counter, 0.5, tags);
}