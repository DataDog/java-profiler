#include <DogFood.hpp>

#include <thread>

int main() {
    while (true) {
        DogFood::Metric(
            "DogFood.MetricTest",
            49.5555,
            DogFood::Counter,
            0.75,
            DogFood::Tags({{"f", "9"}, {"g", "8"}})
        );

        DogFood::Event(
            "DogFood Event",
            "The event was invoked",
            time(NULL)
        );

        DogFood::ServiceCheck(
            "DogFood Service Check",
            DogFood::Status::Warning,
            time(NULL)
        );

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}