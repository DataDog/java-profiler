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

#ifdef __linux__
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>

    #define UDP_SEND(string,port) do {                    \
        struct sockaddr_in client;                        \
        int fd = socket(AF_INET, SOCK_DGRAM, 0);          \
        if (fd == -1) return false;                       \
        std::memset(&client, 0, sizeof(client));          \
        client.sin_family = AF_INET;                      \
        client.sin_port = htons(port);                    \
        client.sin_addr.s_addr = inet_addr("127.0.0.1");  \
        if (sendto(fd, string.c_str(), string.length(),   \
            0, (struct sockaddr*)&client, sizeof(client)) \
            == -1) { close(fd); return false; }           \
        close(fd); } while (0)
#endif

namespace DogFood {

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
// Type
//     The 'Type' of a DataDog 'Metric'
enum Type { Counter, Gauge, Timer, Histogram, Set };

////////////////////////////////////////////////////////////////
// Template
//     Numeric should be an integral or floating-point type
template <typename Numeric>
typename std::enable_if<
    std::is_integral<Numeric>::value      ||
    std::is_floating_point<Numeric>::value,
bool>::type

////////////////////////////////////////////////////////////////
// Metric
//     _name:
//         The name of the 'Metric'
//
//     _number:
//         The numeric value of the 'Metric'
//
//     _type:
//         The type of the 'Metric' e.g. (counter, set)
//
//     _tags: (Optional) (Default is empty map)
//         The tags and values associated with this 'Metric'.
//         If the 'Key' is empty, the entry will be ignored.
//         If the 'Value' is empty and the 'Key' is set,
//         just the value will be ignored.
//
//     _rate: (Optional) (Default is 1.0)
//         The rate [0.0, 1.0] at which the 'Metric' was
//         sampled. e.g. (1.0 => 100% Sampling)
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
    // Verify the name
    //     - Must not be empty or longer than 200 characters
    //     - Must begin with an alphanumeric
    //     - Must not contain '|', ':', or '@'
    if (_name.length() < 1                   ||
        _name.length() > 200                 ||
        !std::isalnum(_name.at(0))           ||
        _name.find('|') != std::string::npos ||
        _name.find(':') != std::string::npos ||
        _name.find('@') != std::string::npos) return false;

    ////////////////////////////////////////////////////////////
    // Verify the rate
    //     - Must be between 0.0 and 1.0 (inclusive)
    if (_rate < 0.0 || _rate > 1.0) return false;
    
    ////////////////////////////////////////////////////////////
    // Add the name and the numeric to the datagram
    std::stringstream stream;
    stream << _name << ":" << _number << "|";

    ////////////////////////////////////////////////////////////
    // Verify the type and append the datagram
    switch (_type)
    {
        case Type::Counter:   stream << "c";  break;
        case Type::Gauge:     stream << "g";  break;
        case Type::Timer:     stream << "ms"; break;
        case Type::Histogram: stream << "h";  break;
        case Type::Set:       stream << "s";  break;
        default:              return false;
    }

    ////////////////////////////////////////////////////////////
    // Add the rate, if not default
    if (_rate != 1.0) stream << "|@" << _rate;

    ////////////////////////////////////////////////////////////
    // Extract the tags string into the stream
    stream << ExtractTags(_tags);

    ////////////////////////////////////////////////////////////
    // Make the datagram
    std::string datagram = stream.str();

    UDP_SEND(datagram, 8125);

    std::cout << datagram << "\n";

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

////////////////////////////////////////////////////////////////
// Event
//     _title:
//         The title of the 'Event'
//
//     _text:
//         The text of the 'Event'.
//         Insert line breaks with '\\n'
//
//     _timestamp: (Optional) (Unix Epoch)
//         The timestamp of the 'Event'
//
//     _hostname: (Optional)
//         The hostname for the 'Event'
//
//     _aggregation_key: (Optional)
//         An aggregation key to group the 'Event' with
//         others that have the same key 'Event'
//
//     _priority: (Optional) (Default is 'Normal')
//         The priority of the 'Event'
//
//     _source_type_name: (Optional)
//         I honestly do not know
//
//     _alert_type: (Optional) (Default is 'Info')
//         The alert type of the 'Event'
//
//     _tags: (Optional) (Default is empty map)
//         The tags and values associated with this 'Metric'.
//         If the 'Key' is empty, the entry will be ignored.
//         If the 'Value' is empty and the 'Key' is set,
//         just the value will be ignored.
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
// Status
//     The 'Status' of a DataDog 'Service Check'
enum class Status {
    OK,
    WARNING,
    CRITICAL,
    UNKNOWN
};

////////////////////////////////////////////////////////////////
// Template
//     Numeric should be an integral or floating-point type
template <typename Numeric>
typename std::enable_if<
    std::is_integral<Numeric>::value      ||
    std::is_floating_point<Numeric>::value,
bool>::type

////////////////////////////////////////////////////////////////
// ServiceCheck
//     _title:
//         The title of the 'Event'
//
//     _status:
//         The 'Status' of the 'Service Check'
//
//     _timestamp: (Optional) (Unix Epoch)
//         The timestamp of the 'Event'
//
//     _hostname: (Optional)
//         The hostname for the 'Event'
//
//     _tags: (Optional) (Default is empty map)
//         The tags and values associated with this 'Metric'.
//         If the 'Key' is empty, the entry will be ignored.
//         If the 'Value' is empty and the 'Key' is set,
//         just the value will be ignored.
//
//     _service_check_message: (Optional)
//         The message describing the 'Service Check'
ServiceCheck
(
    const std::string _title,
    const Status      _status,
    const Numeric     _timestamp  = 0,
    const std::string _hostname   = "",
    const Tags&       _tags       = Tags()
)
noexcept
{
    return true;
}

}      // namespace DogFood
#endif // _DOGFOOD_DOGFOOD_H