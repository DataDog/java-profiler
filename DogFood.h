#ifndef _DOGFOOD_DOGFOOD_H
#define _DOGFOOD_DOGFOOD_H

#include <cctype>
#include <map>
#include <sstream>
#include <string>

#include <iostream>

// metric.name:value|type|@sample_rate|#tag1:value,tag2
// _e{title.length,text.length}:title|text|d:timestamp|h:hostname|p:priority|t:alert_type|#tag1,tag2
// _sc|name|status|d:timestamp|h:hostname|#tag1:value1,tag2,tag3:value3,...|m:service_check_message

// DogFood
//   The goal of 'DogFood' is to prvide a simple, stateless API for communicating with a local DataDog agent
//   

// DogStatsD
//   In order to interface with DogStatsD, a port 
namespace DogFood
{

// Metric Type
enum Type
{
    Counter   = 0,
    Gauge     = 1,
    Timer     = 2,
    Histogram = 3,
    Set       = 4
};

// Event Priority
enum class Priority {
    Low,
    Normal
};

// Event Alert
enum class Alert {
    Info,
    Success,
    Warning,
    Error,
};

// Service Check Status
enum class Status {
    OK,
    WARNING,
    CRITICAL,
    UNKNOWN
};

using Tags = std::map<std::string, std::string>;

// Report
//   - Report a 'Metric' to a DogStatsD agent
//   - Valid if 'Numeric' is Integral of Floating Point and T is a valid 'Type'
template <enum Type T, typename Numeric>
    typename std::enable_if<
        (std::is_integral<Numeric>::value || std::is_floating_point<Numeric>::value) &&
        (T >= Counter && T <= Set),
    bool>::type
Metric(
    const std::string& name,
    const Numeric number,
    const Tags& tags = Tags(),
    const double rate = 1.0
) noexcept {
    // Verify the name
    if (name.length() < 1                   ||
        name.length() > 200                 ||
        !std::isalnum(name.at(0))           ||
        name.find('|') != std::string::npos ||
        name.find(':') != std::string::npos ||
        name.find('@') != std::string::npos
    ) {
        return false;
    }

    // Verify the rate
    if (rate < 0.0 || rate > 1.0) {
        return false;
    }
    
    // Build up the Datagram
    std::stringstream stream;
    stream << name << ":" << number << "|";

    // Check the type
    switch (T) {
        case Type::Counter:   stream << "c";  break;
        case Type::Gauge:     stream << "g";  break;
        case Type::Timer:     stream << "ms"; break;
        case Type::Histogram: stream << "h";  break;
        case Type::Set:       stream << "s";  break;
        default:              return false;
    }

    // Add the rate, if not default
    if (rate != 1.0) {
        stream << "|@" << rate;
    }

    // Check for tags
    if (tags.size() > 0) {
        stream << "|#";
    }

    // Add the tags
    for (const auto p : tags) {
        if (p.first.size()) {
            stream << p.first;
            if (p.second.size()) stream << ":" << p.second;
            stream << ",";
        }
    }

    // Make the datagram
    std::string datagram = stream.str();
    if (datagram.back() == ',') datagram.pop_back();

    std::cout << datagram << "\n";

    return true;
}

// Event

}

#endif //_DOGFOOD_DOGFOOD_H