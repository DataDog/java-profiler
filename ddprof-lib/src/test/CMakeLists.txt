cmake_minimum_required(VERSION 3.14)
project(ddprof-lib-test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ddprof_test
  cpp/ddprof_ut.cpp
)
target_link_libraries(
  ddprof_test
  GTest::gtest_main
)
include_directories(../main/cpp)
target_link_directories(
    ddprof_test PRIVATE
    "../../build/lib/main/debug/linux/x86_64"
    "../../build/lib/main/debug/linux/aarch64"
    "../../build/lib/main/debug/macos/aarch64"
    "../../build/lib/main/debug/macos/x86_64"
    )
target_link_libraries(ddprof_test javaProfiler)

include(GoogleTest)
gtest_discover_tests(ddprof_test)