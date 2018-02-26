# DogFood
A C++ API for reporting DataDog metrics
- Header Only
- Cross Platform
- Communicate with **DogStatsD** agent over UDP

## DataDog
Running the barebones example program in `example/DogFood.example.cpp` produces the following:

![DataDog Capture](https://github.com/garrettsickles/DogFood/blob/master/example/Example.PNG?raw=true)

## Configuration
```cpp
////////////////////////////////////////////////////////////////
// DogStatsD
//
//     Configuration for communicating with the DogStatsD agent
//     Allow overriding the defaults by using `-D` compiler
//     flag.
//     
//     Override the default port
//         E.G. - g++ (...) -DDOGSTATSD_PORT=12345
//
//     Override the default host
//         E.G. - g++ (...) -DDOGSTATSD_PORT="255.255.255.255"
//
#ifndef DOGSTATSD_HOST
	#define DOGSTATSD_HOST "127.0.0.1"
#endif
#ifndef DOGSTATSD_PORT
	#define DOGSTATSD_PORT 8125
#endif
```
## Example

```cpp
// Only need to include this file
// No linkage needed
#include <DogFood/DogFood.h>

// ...std::this_thread::sleep_for
#include <thread>

int main()
{
    // Metrics Forever
    while (true) {
        // Report a 'metric'
        //    - Named "DogFood.MetricTest"
        //    - Value of 49.5555
        //    - Type of Counter
        //    - Sampled rate of 75%
        //    - Tags of f="9" and g="8"
        DogFood::Metric(
            "DogFood.MetricTest",
            49.5555,
            DogFood::Counter,
            0.75,
            DogFood::Tags({{"f", "9"}, {"g", "8"}})
        );
        
        // Report an 'event'
        //    - Named "DogFood Event"
        //    - Message of "The event was invoked"
        //    - At a the current time
        DogFood::Event(
            "DogFood Event",
            "The event was invoked",
            time(NULL)
        );
        
        // Report a 'service_check'
        //    - Named "DogFood Service Check"
        //    - Level of Warning
        //    - At a the current time
        DogFood::ServiceCheck(
            "DogFood Service Check",
            DogFood::Status::Warning,
            time(NULL)
        );
        
        // Sleep for 30 seconds
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
}
```
