#ifndef _DOGFOOD_DOGFOOD_H
#define _DOGFOOD_DOGFOOD_H

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////                                                        ////
////          8888888b.                                     ////
////          888  "Y88b                                    ////
////          888    888                                    ////
////          888    888  .d88b.   .d88b.                   ////
////          888    888 d88""88b d88P"88b                  ////
////          888    888 888  888 888  888                  ////
////          888  .d88P Y88..88P Y88b 888                  ////
////          8888888P"   "Y88P"   "Y88888                  ////
////                                   888                  ////
////                              Y8b d88P                  ////
////                               "Y88P"                   ////
////          8888888888                        888         ////
////          888                               888         ////
////          888                               888         ////
////          8888888     .d88b.   .d88b.   .d88888         ////
////          888        d88""88b d88""88b d88" 888         ////
////          888        888  888 888  888 888  888         ////
////          888        Y88..88P Y88..88P Y88b 888         ////
////          888         "Y88P"   "Y88P"   "Y88888         ////
////                                                        ////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace DogFood {

////////////////////////////////////////////////////////////////
// DogStatsD
//     Configuration for communicating with the DogStatsD agent
//     Allow overriding the defaults by using `-D` compiler
//     flag. 
#ifndef DOGSTATSD_HOST
#define DOGSTATSD_HOST "127.0.0.1"
#endif
#ifndef DOGSTATSD_PORT
#define DOGSTATSD_PORT 8125
#endif

////////////////////////////////////////////////////////////////
// UDP Send
//     Linux and Apple (POSIX-ish)
#if defined(__linux__) || defined(__APPLE__)
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>

    #define UDP_SEND_DATAGRAM(data,size) do {               \
        struct sockaddr_in client;                          \
        int fd = socket(AF_INET, SOCK_DGRAM, 0);            \
        if (fd == -1) return false;                         \
        std::memset(&client, 0, sizeof(client));            \
        client.sin_family = AF_INET;                        \
        client.sin_port = htons(DOGSTATSD_PORT);            \
        client.sin_addr.s_addr = inet_addr(DOGSTATSD_HOST); \
        if (sendto(fd,data,size,0,(struct sockaddr*)&client,\
        sizeof(client)) == -1) { close(fd); return false; } \
        close(fd); } while (0)

//     Microsoft Windows 
#elif defined(_MSC_VER)
    #define UDP_SEND_DATAGRAM(data,size)\
        static_assert(false, "Microsoft not supported!");
#else
    #error "Well, sorry for your weird OS..."
#endif


//     Send a c++ std::string
#define DOGFOOD_SEND_STDSTRING(string)\
    UDP_SEND_DATAGRAM(string.c_str(),string.length())

////////////////////////////////////////////////////////////////
//                                                            //
//         88888888888                                        //
//             888                                            //
//             888                                            //
//             888      8888b.   .d88b.  .d8888b              //
//             888         "88b d88P"88b 88K                  //
//             888     .d888888 888  888 "Y8888b.             //
//             888     888  888 Y88b 888      X88             //
//             888     "Y888888  "Y88888  88888P'             //
//                                   888                      //
//                              Y8b d88P                      //
//                               "Y88P"                       //
//                                                            //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Tags
//     Use a map of string->string for storing 'Key'->'Value'
//     pairs. If the 'Value' is empty, only the 'Key' is used.
using Tags = std::map<std::string, std::string>;

////////////////////////////////////////////////////////////////
// ExtractTags
//     - Return a string modeling the a Tags object
inline std::string ExtractTags(const Tags& _tags)
{
    // The tags string to build up
    std::string stream;

    // Check for the presence of tags
    if (_tags.size() > 0) stream += "|#";

    ////////////////////////////////////////////////////////////
    // Add each tags
    for (const auto p : _tags)
    {
        // If the 'Key' is not empty
        if (p.first.size())
        {
            // Append the 'Key'
            stream +=p.first;

            // If the 'Value' is not empty
            if (p.second.size()) stream += (":" + p.second);

            // Append a comma to indicate the next 'Key'
            stream += ",";
        }
    }

    // Remove the trailing comma if present
    if (stream.back() == ',') stream.pop_back();

    return stream;
}

////////////////////////////////////////////////////////////////
// ValidateMetricName
//     - Must not be empty or longer than 200 characters
//     - Must begin with an alphanumeric
//     - Must not contain '|', ':', or '@'
inline bool ValidateMetricName(const std::string& _name)
{
    return
        _name.length() > 1                   &&
        _name.length() < 200                 &&
        std::isalnum(_name.at(0))            &&
        _name.find('|') == std::string::npos &&
        _name.find(':') == std::string::npos &&
        _name.find('@') == std::string::npos;
}

////////////////////////////////////////////////////////////////
// ValidateSampleRate
//     - Must be between 0.0 and 1.0 (inclusive)
inline bool ValidateSampleRate(const float _rate)
{
    return
        _rate >= 0.0 &&
        _rate <= 1.0;
}

////////////////////////////////////////////////////////////////
// Type
//     The 'Type' of a DataDog 'Metric'
enum Type { Counter, Gauge, Timer, Histogram, Set };

////////////////////////////////////////////////////////////////
// ValidateSampleRate
//     - Must be between 0.0 and 1.0 (inclusive)
inline bool ValidateType(const Type& _type)
{
    switch (_type)
    {
        case Type::Counter:
        case Type::Gauge:
        case Type::Timer:
        case Type::Histogram:
        case Type::Set:
            return true;
        default:
            return false;
    }
}

////////////////////////////////////////////////////////////////
// EscapeEventText
//     - Insert line breaks with an escaped slash (\\n)
inline std::string EscapeEventText(const std::string& _text)
{
    // String buffer
    std::string buffer;

    // Iterate through input string searching for '\n'
    for (const char c : _text)
    {
        // Replace newline literals with '\\n'
        if (c == '\n') buffer.append("\\\\n");
        else           buffer.push_back(c);
    }

    // Return the escaped buffer
    return buffer;
}

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
//     'metric.name:value|type|@sample_rate|#tag1:value,tag2'
//
//     - metric.name
//         A string with no colons, bars, or @ characters.
//         See the metric naming policy.
//     - value
//         An integer or float.
//     - type
//         'c' for counter, 'g' for gauge, 'ms' for timer,
//         'h' for histogram, 's' for set.
//     - @sample_rate
//         (Optional)
//             A float between 0 and 1, inclusive.
//             Only works with counter, histogram,
//             and timer metrics. Default is 1
//             (i.e. sample 100% of the time).
//     - tags
//         (Optional)
//             A comma separated list of tags.
//             Use colons for key/value tags, i.e. env:prod.
//             The key device is reserved; Datadog drops a
//             user-added tag like device:foobar.

////////////////////////////////////////////////////////////////
// Samples
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

////////////////////////////////////////////////////////////////
// Template
//     Numeric should be an integral or floating-point type
template <typename Numeric>
typename std::enable_if<
    std::is_integral<Numeric>::value      ||
    std::is_floating_point<Numeric>::value,
bool>::type
Metric
(
    const std::string _name,
    const Numeric     _number,
    const Type        _type,
    const double      _rate     = 1.0,
    const Tags&       _tags     = Tags()
)
noexcept
{
    ////////////////////////////////////////////////////////////
    // Declare the datagram stream
    std::stringstream datagram;

    ////////////////////////////////////////////////////////////
    // Validate the name
    if (!ValidateMetricName(_name)) return false;

    ////////////////////////////////////////////////////////////
    // Verify the rate
    //     - Must be between 0.0 and 1.0 (inclusive)
    if (!ValidateSampleRate(_rate)) return false;
    
    ////////////////////////////////////////////////////////////
    // Add the name and the numeric to the datagram
    // `metric.name:value|`
    datagram << _name << ":" << _number << "|";

    ////////////////////////////////////////////////////////////
    // Verify the type and append the datagram
    // `c` or `g` or `ms` or `h` or `s`
    switch (_type)
    {
        case Type::Counter:   datagram << "c";  break;
        case Type::Gauge:     datagram << "g";  break;
        case Type::Timer:     datagram << "ms"; break;
        case Type::Histogram: datagram << "h";  break;
        case Type::Set:       datagram << "s";  break;
        default:              return false;
    }

    ////////////////////////////////////////////////////////////
    // Add the rate to the datagram if present
    // `|@sample_rate`
    if (_rate != 1.0)
        datagram << "|@" << _rate;

    ////////////////////////////////////////////////////////////
    // Extract the tags string into the datagram if present
    // `|#tag1:value,tag2`
    datagram << ExtractTags(_tags);

    ////////////////////////////////////////////////////////////
    // Send the datagram
    DOGFOOD_SEND_STDSTRING(datagram.str());

    return true;
}

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
//     '_e{title.length,text.length}:title|text|d:timestamp|
//      h:hostname|p:priority|t:alert_type|#tag1,tag2'
//
//     - _e
//         The datagram must begin with _e
//     - title
//         Event title.
//     - text
//         Event text.
//         Insert line breaks with an escaped slash (\\n)
//     - d:timestamp
//         (Optional)
//             Add a timestamp to the event.
//             Default is the current Unix epoch timestamp.
//     - h:hostname
//         (Optional)
//             Add a hostname to the event. No default.
//     - k:aggregation_key
//         (Optional)
//             Add an aggregation key to group the event with
//             others that have the same key. No default.
//     - p:priority
//         (Optional)
//             Set to ‘normal’ or ‘low’. Default ‘normal’.
//     - s:source_type_name
//         (Optional)
//             Add a source type to the event. No default.
//     - t:alert_type
//         (Optional)
//             Set to ‘error’, ‘warning’, ‘info’ or ‘success’.
//             Default ‘info’.
//     - #tag1:value1,tag2,tag3:value3...
//         (Optional)
//             The colon in tags is part of the tag list string
//             and has no parsing purpose like for the other
//             parameters. No default.

////////////////////////////////////////////////////////////////
// Samples
//     # Send an exception
//     '_e{21,36}:An exception occurred|Cannot parse CSV file
//      from 10.0.0.17|t:warning|#err_type:bad_file'
//
//     # Send an event with a newline in the text
//     '_e{21,42}:An exception occurred|Cannot parse JSON
//      request:\\n{"foo: "bar"}|p:low|#err_type:bad_request'

////////////////////////////////////////////////////////////////
// Priority
//     The 'Priority' of a DataDog 'Event'
enum class Priority { Low, Normal };

////////////////////////////////////////////////////////////////
// Alert
//     The 'Alert' type of a DataDog 'Event'
enum class Alert { Info, Success, Warning, Error };

////////////////////////////////////////////////////////////////
// Template
//     Numeric should be an integral or floating-point type
template <typename Numeric>
typename std::enable_if<
    std::is_integral<Numeric>::value      ||
    std::is_floating_point<Numeric>::value,
bool>::type
Event
(
    const std::string _title,
    const std::string _text,
    const Numeric     _timestamp         = 0,
    const std::string _hostname          = "",
    const std::string _aggregation_key   = "",
    const Priority    _priority          = Priority::Normal,
    const std::string _source_type_name  = "",
    const Alert       _alert_type        = Alert::Info,
    const Tags&       _tags              = Tags()
)
noexcept
{
    ////////////////////////////////////////////////////////////
    // Declare the datagram stream
    std::stringstream datagram;

    ////////////////////////////////////////////////////////////
    // Get the escaped text
    const std::string _etext = EscapeEventText(_text);

    ////////////////////////////////////////////////////////////
    // Add the title and text to the datagram
    // `_e{title.length,text.length}:title|text|`
    datagram
        << "_e{" << _title.length() << "," << _etext.length()
        << "}:"  << _title          << "|" << _etext;

    ////////////////////////////////////////////////////////////
    // Add the timestamp to the datagram if present
    if (_timestamp != static_cast<Numeric>(0))
        datagram << "|d:" << _timestamp;

    ////////////////////////////////////////////////////////////
    // Add the hostname to the datagram if present
    if (_hostname != "")
        datagram << "|h:" << _hostname;

    ////////////////////////////////////////////////////////////
    // Add the priority to the datagram if present
    if (_priority == Priority::Low)
        datagram << "|p:" << "low";

    ////////////////////////////////////////////////////////////
    // Add the source type name to the datagram if present
    if (_source_type_name != "")
        datagram << "|s:" << _source_type_name;

    ////////////////////////////////////////////////////////////
    // Verify the alert type and append the datagram if valid
    // `success` or `warning` or `error`
    switch (_alert_type)
    {
        case Alert::Success: datagram << "|t:success"; break;
        case Alert::Warning: datagram << "|t:warning"; break;
        case Alert::Error:   datagram << "|t:error";   break;
        default:                                       break;
    }

    ////////////////////////////////////////////////////////////
    // Extract the tags string into the datagram
    // `|#tag1:value,tag2`
    datagram << ExtractTags(_tags);

    ////////////////////////////////////////////////////////////
    // Send the datagram
    DOGFOOD_SEND_STDSTRING(datagram.str());

    return true;
}

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
//     # Send a CRITICAL status for a remote connection
//     '_sc|Redis connection|2|#redis_instance:10.0.0.16:6379|
//      m:Redis connection timed out after 10s'

////////////////////////////////////////////////////////////////
// Status
//     The 'Status' of a DataDog 'Service Check'
enum class Status {
    Ok,
    Warning,
    Critical,
    Unknown
};

////////////////////////////////////////////////////////////////
// Template
//     Numeric should be an integral or floating-point type
template <typename Numeric>
typename std::enable_if<
    std::is_integral<Numeric>::value      ||
    std::is_floating_point<Numeric>::value,
bool>::type
ServiceCheck
(
    const std::string _name,
    const Status      _status,
    const Numeric     _timestamp = 0,
    const std::string _hostname  = "",
    const std::string _message   = "",
    const Tags&       _tags      = Tags()
)
noexcept
{
    ////////////////////////////////////////////////////////////
    // Declare the datagram stream
    std::stringstream datagram;

    ////////////////////////////////////////////////////////////
    // Add the name to the datagram
    // `_sc|name|`
    datagram << "_sc|" << _name << "|";

    ////////////////////////////////////////////////////////////
    // Verify the status and append the datagram if valid
    // `0` or `1` or `2` or `3`
    switch (_status)
    {
        case Status::Ok:       datagram << "0"; break;
        case Status::Warning:  datagram << "1"; break;
        case Status::Critical: datagram << "2"; break;
        case Status::Unknown:  datagram << "3"; break;
        default:               return false;
    }

    ////////////////////////////////////////////////////////////
    // Add the timestamp to the datagram if present
    if (_timestamp != static_cast<Numeric>(0))
        datagram << "|d:" << _timestamp;

    ////////////////////////////////////////////////////////////
    // Add the hostname to the datagram if present
    if (_hostname != "")
        datagram << "|h:" << _hostname;

    ////////////////////////////////////////////////////////////
    // Extract the tags string into the datagram
    // `|#tag1:value,tag2`
    datagram << ExtractTags(_tags);

    ////////////////////////////////////////////////////////////
    // Add the service check message name
    // to the datagram if present
    if (_message != "")
        datagram << "|m:" << _message;

    ////////////////////////////////////////////////////////////
    // Send the datagram
    DOGFOOD_SEND_STDSTRING(datagram.str());

    return true;
}

}      // namespace DogFood
#endif // _DOGFOOD_DOGFOOD_H

// Well, I guess that is the end. Until next time, folks!
