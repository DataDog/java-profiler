# DogFood
[(See us on DataDog's developer site)](https://docs.datadoghq.com/developers/libraries/)

[![Build Status](https://travis-ci.org/garrettsickles/DogFood.svg?branch=master)](https://travis-ci.org/garrettsickles/DogFood)
[![Build status](https://ci.appveyor.com/api/projects/status/x9e35p9nknds5p13/branch/master?svg=true)](https://ci.appveyor.com/project/garrettsickles/dogfood/branch/master)

A C++ API for reporting DataDog metrics
- Header Only
- Stateless
- Cross Platform
- **UDP** and **UDS** (linux only) communication with **DogStatsD** agent

## Simple Example
Running the barebones example program in [`example/simple_example.cpp`](example/simple_example.cpp) produces the following:

![DataDog Capture](https://github.com/garrettsickles/DogFood/blob/master/example/Example.PNG?raw=true)

## Before You Start
This project is used for communicating with a **DataDog Agent**

If you do not have a [DataDog Agent](https://docs.datadoghq.com/agent) installed, please install it and connect it to your account!
## Configuration

### UDP - User Datagram Protocol (Custom)
Configure DogFood to send metrics to a custom **host** and **port** over **UDP**

Here is an example in [`example/simple_example_udp.cpp`](example/simple_example_udp.cpp)
```cpp
DogFood::Send(DogFood::Metric(
    "DogFood.MetricTest",
    49.5555,
    DogFood::Counter,
    0.75,
    DogFood::Tags({ { "f", "9" }, { "g", "8" } })
), DogFood::UDP("127.0.0.1", 8125));
```

### UDS - Unix Domain Sockets (Custom)
Configure DogFood to send metrics to a custom **host** and **port** over **UDP**

Here is an example in [`example/simple_example_linux_uds.cpp`](example/simple_example_linux_uds.cpp)
```cpp
DogFood::Send(DogFood::Metric(
    "DogFood.MetricTest",
    49.5555,
    DogFood::Counter,
    0.75,
    DogFood::Tags({ { "f", "9" }, { "g", "8" } })
), DogFood::UDS("/var/run/datadog/dsd.socket"));
```

### UDP - User Datagram Protocol (At build time)
Configure DogFood to send metrics to a custom **host** and **port** over **UDP**

Here is an example in [`example/simple_example.cpp`](example/simple_example.cpp)
```cpp
// At compile time override the default host & default port
//   (Please do not compile with 255.255.255.255)
g++ (...) -DDOGSTATSD_HOST="255.255.255.255" -DDOGSTATSD_PORT=12345

// At compile time in the source
#define DOGSTATSD_HOST "127.0.0.1"
#define DOGSTATSD_PORT 8125


// By default will send over UDP to DOGSTATSD_HOST:DOGSTATSD_PORT
DogFood::Send(DogFood::Metric(
    "DogFood.MetricTest",
    49.5555,
    DogFood::Counter,
    0.75,
    DogFood::Tags({ { "f", "9" }, { "g", "8" } })
));
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
        DogFood::Send(DogFood::Metric(
            "DogFood.MetricTest",
            49.5555,
            DogFood::Counter,
            0.75,
            DogFood::Tags({ { "f", "9" }, { "g", "8" } })
        ));
        
        // Report an 'event'
        //    - Named "DogFood Event"
        //    - Message of "The event was invoked"
        //    - At a the current time
        DogFood::Send(DogFood::Event(
            "DogFood Event",
            "The event was invoked",
            time(NULL)
        ));
        
        // Report a 'service_check'
        //    - Named "DogFood Service Check"
        //    - Level of Warning
        //    - At a the current time
        DogFood::Send(DogFood::ServiceCheck(
            "DogFood Service Check",
            DogFood::Status::Warning,
            time(NULL)
        ));
        
        // Sleep for 30 seconds
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
}
```

## Metric
```cpp
////////////////////////////////////////////////////////////////
//                                                            //
//     888b     d888          888            d8b              //
//     8888b   d8888          888            Y8P              //
//     88888b.d88888          888                             //
//     888Y88888P888  .d88b.  888888 888d888 888  .d8888b     //
//     888 Y888P 888 d8P  Y8b 888    888P"   888 d88P"        //
//     888  Y8P  888 88888888 888    888     888 888          //
//     888   "   888 Y8b.     Y88b.  888     888 Y88b.        //
//     888       888  "Y8888   "Y888 888     888  "Y8888P     //
//                                                            //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Format
//
//     'metric.name:value|type|@sample_rate|#tag1:value,tag2'
//
//     - metric.name
//         A string with no colons, bars, or @ characters.
//         See the metric naming policy.
//
//     - value
//         An integer or float.
//
//     - type
//         'c' for counter, 'g' for gauge, 'ms' for timer,
//         'h' for histogram, 's' for set.
//
//     - @sample_rate
//         (Optional)
//             A float between 0 and 1, inclusive.
//             Only works with counter, histogram,
//             and timer metrics. Default is 1
//             (i.e. sample 100% of the time).
//
//     - tags
//         (Optional)
//             A comma separated list of tags.
//             Use colons for key/value tags, i.e. env:prod.
//             The key device is reserved; Datadog drops a
//             user-added tag like device:foobar.
//

////////////////////////////////////////////////////////////////
// Samples
//
//     # Increment the page.views counter
//     'page.views:1|c'
//
//     # Record the fuel tank is half-empty
//     'fuel.level:0.5|g'
//
//     # Sample the song length histogram half of the time
//     'song.length:240|h|@0.5'
//
//     # Track a unique visitor to the site
//     'users.uniques:1234|s'
//
//     # Increment the active users counter, tag by country
//     'users.online:1|c|#country:china'
//
//     # Track active China users and use a sample rate
//     'users.online:1|c|@0.5|#country:china'
//

////////////////////////////////////////////////////////////////
// Type
//
//     The 'Type' of a DataDog 'Metric'
//
enum Type {
    Counter,
    Gauge,
    Timer,
    Histogram,
    Set
};

std::string Metric(
    const std::string _name,
    const ValueType   _value,
    const Type        _type,
    const double      _rate = 1.0,
    const Tags&       _tags = Tags()
);
```


## Event
```cpp
////////////////////////////////////////////////////////////////
//                                                            //
//        8888888888                            888           //
//        888                                   888           //
//        888                                   888           //
//        8888888    888  888  .d88b.  88888b.  888888        //
//        888        888  888 d8P  Y8b 888 "88b 888           //
//        888        Y88  88P 88888888 888  888 888           //
//        888         Y8bd8P  Y8b.     888  888 Y88b.         //
//        8888888888   Y88P    "Y8888  888  888  "Y888        //
//                                                            //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Format
//
//     '_e{title.length,text.length}:title|text|d:timestamp|
//      h:hostname|p:priority|t:alert_type|#tag1,tag2'
//
//     - _e
//         The datagram must begin with _e
//
//     - title
//         Event title.
//
//     - text
//         Event text.
//         Insert line breaks with an escaped slash (\\n)
//
//     - d:timestamp
//         (Optional)
//             Add a timestamp to the event.
//             Default is the current Unix epoch timestamp.
//
//     - h:hostname
//         (Optional)
//             Add a hostname to the event. No default.
//
//     - k:aggregation_key
//         (Optional)
//             Add an aggregation key to group the event with
//             others that have the same key. No default.
//
//     - p:priority
//         (Optional)
//             Set to ‘normal’ or ‘low’. Default ‘normal’.
//
//     - s:source_type_name
//         (Optional)
//             Add a source type to the event. No default.
//
//     - t:alert_type
//         (Optional)
//             Set to ‘error’, ‘warning’, ‘info’ or ‘success’.
//             Default ‘info’.
//
//     - #tag1:value1,tag2,tag3:value3...
//         (Optional)
//             The colon in tags is part of the tag list string
//             and has no parsing purpose like for the other
//             parameters. No default.
//

////////////////////////////////////////////////////////////////
// Samples
//
//     # Send an exception
//     '_e{21,36}:An exception occurred|Cannot parse CSV file
//      from 10.0.0.17|t:warning|#err_type:bad_file'
//
//     # Send an event with a newline in the text
//     '_e{21,42}:An exception occurred|Cannot parse JSON
//      request:\\n{"foo: "bar"}|p:low|#err_type:bad_request'
//

////////////////////////////////////////////////////////////////
// Priority
//
//     The 'Priority' of a DataDog 'Event'
//
enum class Priority {
    Low,
    Normal
};

////////////////////////////////////////////////////////////////
// Alert
//
//     The 'Alert' type of a DataDog 'Event'
//
enum class Alert {
    Info,
    Success,
    Warning,
    Error
};

std::string Event(
    const std::string _title,
    const std::string _text,
    const Numeric     _timestamp         = 0,
    const std::string _hostname          = "",
    const std::string _aggregation_key   = "",
    const Priority    _priority          = Priority::Normal,
    const std::string _source_type_name  = "",
    const Alert       _alert_type        = Alert::Info,
    const Tags&       _tags              = Tags()
);
```

## Service Check
```cpp
////////////////////////////////////////////////////////////////
//                                                            //
//   .d8888b.                            d8b                  //
//  d88P  Y88b                           Y8P                  //
//  Y88b.                                                     //
//   "Y888b.    .d88b.  888d888 888  888 888  .d8888b .d88b.  //
//      "Y88b. d8P  Y8b 888P"   888  888 888 d88P"   d8P  Y8b //
//        "888 88888888 888     Y88  88P 888 888     88888888 //
//  Y88b  d88P Y8b.     888      Y8bd8P  888 Y88b.   Y8b.     //
//   "Y8888P"   "Y8888  888       Y88P   888  "Y8888P "Y8888  //
//                                                            //
//                                                            //
//                                                            //
//         .d8888b.  888                        888           //
//        d88P  Y88b 888                        888           //
//        888    888 888                        888           //
//        888        88888b.   .d88b.   .d8888b 888  888      //
//        888        888 "88b d8P  Y8b d88P"    888 .88P      //
//        888    888 888  888 88888888 888      888888K       //
//        Y88b  d88P 888  888 Y8b.     Y88b.    888 "88b      //
//         "Y8888P"  888  888  "Y8888   "Y8888P 888  888      //
//                                                            //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Format
//     '_sc|name|status|d:timestamp|h:hostname|#tag1:value1,
//      tag2,tag3:value3,...|m:service_check_message'
//
//     - _sc
//         The datagram must begin with _sc.
//     - name
//         Service check name.
//     - status
//         Integer corresponding to the check status.
//         (OK = 0, WARNING = 1, CRITICAL = 2, UNKNOWN = 3).
//     - d:timestamp
//         (Optional)
//             Add a timestamp to the event.
//             Default is the current Unix epoch timestamp.
//     - h:hostname
//         (Optional)
//             Add a hostname to the event. No default.
//     - #tag1:value1,tag2,tag3:value3...
//         (Optional)
//             The colon in tags is part of the tag list string
//             and has no parsing purpose like for the other
//             parameters. No default.
//     - m:service_check_message
//         (Optional)
//             Add a message describing the current state of
//             the service check. This field MUST be positioned
//             last among the metadata fields. No default.

////////////////////////////////////////////////////////////////
// Samples
//
//     # Send a CRITICAL status for a remote connection
//     '_sc|Redis connection|2|#redis_instance:10.0.0.16:6379|
//      m:Redis connection timed out after 10s'

////////////////////////////////////////////////////////////////
// Status
//
//     The 'Status' of a DataDog 'Service Check'
//
enum class Status {
    Ok,
    Warning,
    Critical,
    Unknown
};

////////////////////////////////////////////////////////////////
// Template
//
//     Numeric should be an integral or floating-point type
//
std::string ServiceCheck(
    const std::string _name,
    const Status      _status,
    const Numeric     _timestamp = 0,
    const std::string _hostname  = "",
    const std::string _message   = "",
    const Tags&       _tags      = Tags()
);
```
