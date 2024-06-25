#include <DogFood.hpp>

#include <thread>

int main() {
    const auto config = DogFood::UDP("127.0.0.1", 8125);
    while (true) {
        DogFood::Send(
            DogFood::Metric(
            "DogFood.MetricTest",
            49.5555,
            DogFood::Counter,
            0.75,
            DogFood::Tags({ { "f", "9" }, { "g", "8" } })
        ), config);

        DogFood::Send(
            DogFood::Event(
            "DogFood Event",
            "The event was invoked",
            time(NULL)
        ), config);

        DogFood::Send(DogFood::ServiceCheck(
            "DogFood Service Check",
            DogFood::Status::Warning,
            time(NULL)
        ), config);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}