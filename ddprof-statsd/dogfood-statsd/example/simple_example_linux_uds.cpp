#include <DogFood.hpp>

#include <thread>

/*
 * 1. Set datadog agent to use UDS in /etc/datadog-agent/datadog.yaml
 *    - Set dogstatsd_socket to /var/run/datadog/dsd.socket
 *      e.g. - `dogstatsd_socket: /var/run/datadog/dsd.socket`
 * 2. Add permissions for dd-agent
 *    - mkdir /var/run/datadog/
 *    - sudo chown dd-agent:dd-agent -R /var/run/datadog/
 */
int main() {
    while (true) {
        DogFood::Send(
            DogFood::Metric(
            "DogFood.MetricTest",
            49.5555,
            DogFood::Counter,
            0.75,
            DogFood::Tags({ { "f", "9" }, { "g", "8" } })
        ), DogFood::UDS("/var/run/datadog/dsd.socket"));

        DogFood::Send(
            DogFood::Event(
            "DogFood Event",
            "The event was invoked",
            time(NULL)
        ), DogFood::UDS("/var/run/datadog/dsd.socket"));

        DogFood::Send(DogFood::ServiceCheck(
            "DogFood Service Check",
            DogFood::Status::Warning,
            time(NULL)
        ), DogFood::UDS("/var/run/datadog/dsd.socket"));

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}