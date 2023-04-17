cmake_minimum_required(VERSION 3.14)
project(ddprof-lib-test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(./Sanitizers.cmake)
include(./AddUnitTests.cmake)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(OS_SUFFIX "linux")
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OS_SUFFIX "macos")
endif()

# uncomment the following lines to print out various build related variables
# include(CMakePrintHelpers)
# cmake_print_variables(SRC_FILES PROJECT_SOURCE_DIR CMAKE_SYSTEM_NAME)

# Include all *.cpp files from the cpp folder
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/cpp/*.cpp"
)

# not all source files are required to run gtests -
#   new source files should be added when a test is complaining about missing symbols
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/../main/cpp/os_${OS_SUFFIX}.cpp"
    "${PROJECT_SOURCE_DIR}/../main/cpp/context.cpp"
    "${PROJECT_SOURCE_DIR}/../main/cpp/counters.cpp"
)

## Declare unit tests with add_unit_test / add_java_unit_test
add_unit_test(ddprof-lib-test
  NO_DETECT_LEAKS
  ${TEST_FILES}
  ${SRC_FILES})
