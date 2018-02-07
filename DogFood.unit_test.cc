#include "DogFood.h"

int main() {
    const auto tags = DogFood::Tags({{"a", "1"}, {"b", "2"}});
    auto i = DogFood::Metric<DogFood::Counter>("metric", 69.523456236, tags);
}