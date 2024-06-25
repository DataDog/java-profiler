#include <DogFood.hpp>

#include "unittest.hpp"

////////////////////////////////////////////////////////////////
// Unit Test
//
// Tags
////////////////////////////////////////////////////////////////
void UnitTest::Setup() {
    
    ////////////////////////////////////////////////////////////////
    // Extract Tags
    ////////////////////////////////////////////////////////////////

    // No tags
    AddTest("Extract Tags", "No tags", [](void) {
        DogFood::Tags tags;

        AssertEqual(DogFood::ExtractTags(tags),
            std::string(""),
            "Tags string should be empty"
        );
    });
    
    // Single key tag
    AddTest("Extract Tags", "Single key tag", [](void) {
        DogFood::Tags tags;

        tags.push_back(DogFood::Tag("tag1"));

        AssertEqual(DogFood::ExtractTags(tags),
            std::string("|#tag1"),
            "Tag string should contain one tag"
        );
    });

    // Multiple key tags
    AddTest("Extract Tags", "Multiple key tags", [](void) {
        DogFood::Tags tags;

        tags.push_back(DogFood::Tag("tag1"));
        tags.push_back(DogFood::Tag("tag2"));
        tags.push_back(DogFood::Tag("tag3"));

        AssertEqual(DogFood::ExtractTags(tags),
            std::string("|#tag1,tag2,tag3"),
            "Tag string should contain three tags"
        );
    });

    // Single key-value tag
    AddTest("Extract Tags", "Single key-value tag", [](void) {
        DogFood::Tags tags;

        tags.push_back(DogFood::Tag("tag1", "thing1"));

        AssertEqual(DogFood::ExtractTags(tags), std::string("|#tag1:thing1"),
            "Tag string should contain single key-value tag"
        );
    });

    // Multiple key-value tags
    AddTest("Extract Tags", "Multiple key-value tags", [](void) {
        DogFood::Tags tags;

        tags.push_back(DogFood::Tag("tag1", "thing1"));
        tags.push_back(DogFood::Tag("tag2", "thing2"));
        tags.push_back(DogFood::Tag("tag3", "thing3"));


        AssertEqual(DogFood::ExtractTags(tags),
            std::string("|#tag1:thing1,tag2:thing2,tag3:thing3"),
            "Tag string should contain multiple key-value tags"
        );
    });
}