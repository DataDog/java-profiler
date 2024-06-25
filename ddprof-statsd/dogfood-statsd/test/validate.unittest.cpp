#include <cstdlib>
#include <ctime>

#include <DogFood.hpp>

#include "unittest.hpp"

////////////////////////////////////////////////////////////////
// Unit Test
//
// Validate
////////////////////////////////////////////////////////////////
void UnitTest::Setup() {

    ////////////////////////////////////////////////////////////////
    // Metric Name
    ////////////////////////////////////////////////////////////////

    // Name length
    AddTest("Metric Name", "Name Length", [](void) {
        // Too short
        {
            const std::string too_short = "";
            AssertFalse(DogFood::ValidateMetricName(too_short), "Empty name should not be valid");
        }

        // Valid
        for (int i = 1; i < 201; i++)
        {
            std::string just_right(i, 'x');
            AssertTrue(DogFood::ValidateMetricName(just_right), "Name of length " + std::to_string(i) + " should be valid");
        }

        // Too long
        {
            const std::string too_long(201, 'x');
            AssertFalse(DogFood::ValidateMetricName(too_long), "Name longer than 201 characters should not be valid");
        }

    });

    // Invalid name characters
    AddTest("Metric Name", "Invalid characters", [](void) {
        std::string test_name = "Metric Name";
        for (char c = 0; c < 127; c++) {
            test_name[6] = c;

            // Valid name
            if (std::isalnum(c) || c == '_' || c == '.') {
                std::string message = "Name containing ASCII '" + std::to_string(c) + "' should be valid";
                AssertTrue(DogFood::ValidateMetricName(test_name), message);
            }
            
            // Invalid name
            else {
                std::string message = "Name containing ASCII '" + std::to_string(c) + "' should not be valid: ";
                AssertFalse(DogFood::ValidateMetricName(test_name), message);
            }
        }
    });

    // Invalid starting character
    AddTest("Metric Name", "Invalid starting character", [](void) {
        std::string test_name = "MetricName";
        for (char c = 0; c < 127; c++) {
            test_name[0] = c;

            // Valid first letter
            if (std::isalpha(c)) {
                std::string message = "Name beginning with ASCII '" + std::to_string(c) + "' should be valid";
                AssertTrue(DogFood::ValidateMetricName(test_name), message);
            }
            
            // Invalid first letter
            else {
                std::string message = "Name beginning with ASCII '" + std::to_string(c) + "' should not be valid: ";
                AssertFalse(DogFood::ValidateMetricName(test_name), message);
            }
        }
    });

    ////////////////////////////////////////////////////////////////
    // Tags
    ////////////////////////////////////////////////////////////////
    
    // Tags length
    AddTest("Tags", "Tags Length", [](void) {
        // Too short
        {
            const std::string too_short = "";
            AssertFalse(DogFood::ValidateTags(too_short), "Empty tags should not be valid");
        }

        // Valid
        for (int i = 1; i < 201; i++)
        {
            std::string just_right(i, 'x');
            AssertTrue(DogFood::ValidateTags(just_right), "Tags of length " + std::to_string(i) + " should be valid");
        }

        // Too long
        {
            const std::string too_long(201, 'x');
            AssertFalse(DogFood::ValidateTags(too_long), "Tags longer than 200 characters should not be valid");
        }

    });

    // Invalid tags characters
    AddTest("Tags", "Invalid characters", [](void) {
        std::string test_name = "Key Value";
        for (char c = 0; c < 127; c++) {
            test_name[3] = c;

            // Valid name
            if (std::isalnum(c) ||
                c == '_' || c == '-' ||
                c == ':' || c == '.' ||
                c == '/' || c == '\\') {
                std::string message = "Tags containing ASCII '" + std::to_string(c) + "' should be valid";
                AssertTrue(DogFood::ValidateTags(test_name), message);
            }
            
            // Invalid name
            else {
                std::string message = "Tags containing ASCII '" + std::to_string(c) + "' should not be valid: ";
                AssertFalse(DogFood::ValidateTags(test_name), message);
            }
        }
    });

    // Invalid starting character
    AddTest("Tags", "Invalid starting character", [](void) {
        std::string test_name = "Key:Value";
        for (char c = 0; c < 127; c++) {
            test_name[0] = c;

            // Valid first letter
            if (std::isalpha(c)) {
                std::string message = "Tags beginning with ASCII '" + std::to_string(c) + "' should be valid";
                AssertTrue(DogFood::ValidateTags(test_name), message);
            }
            
            // Invalid first letter
            else {
                std::string message = "Tags beginning with ASCII '" + std::to_string(c) + "' should not be valid: ";
                AssertFalse(DogFood::ValidateTags(test_name), message);
            }
        }
    });

    // Invalid ending character
    AddTest("Tags", "Invalid ending character", [](void) {
        std::string test_name = "Key:Value:";

        AssertFalse(DogFood::ValidateTags(test_name), "Tags ending with ':' should not be valid");
    });

    ////////////////////////////////////////////////////////////////
    // Sample Rate
    ////////////////////////////////////////////////////////////////
    AddTest("Sample Rate", "Sample Rate", [](void) {
        // Too small sample rate
        AssertFalse(DogFood::ValidateSampleRate(-1.0), "Negative sample rate should not be valid");

        // 0.0 sample rate
        AssertTrue(DogFood::ValidateSampleRate(0.0), "Sample rate equal to 0 should be valid");

        // (0.0, 1.0) sample rate
        std::srand(std::time(NULL));
        for (int i = 0; i < 10; i++) {
            const double rate = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
            AssertTrue(DogFood::ValidateSampleRate(rate), "Positive sample rate " + std::to_string(rate) + " between 0 and 1 should be valid");
        }

        // 1.0 sample rate
        AssertTrue(DogFood::ValidateSampleRate(1.0), "Sample rate equal to 1 should be valid");
        AssertFalse(DogFood::ValidateSampleRate(2.0), "Positive sample rate greater than 1 should not be valid");
    });

    ////////////////////////////////////////////////////////////////
    // Payload Size
    ////////////////////////////////////////////////////////////////
    AddTest("Payload Size", "Payload Size", [](void) {
        const std::string max_payload(65507, 'x');
        AssertTrue(DogFood::ValidatePayloadSize(max_payload), "Payload should not be longer than 65507 bytes");
    });
}