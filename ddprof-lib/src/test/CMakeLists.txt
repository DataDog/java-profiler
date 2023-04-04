cmake_minimum_required(VERSION 3.14)
project(ddprof-lib-test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

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

# Include all *.cpp files from the cpp folder
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/cpp/*.cpp"
)

file(GLOB_RECURSE OBJ_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/../../build/obj/main/debug/**/*.o"
)

add_executable(
  ddprof-lib-test
  ${SRC_FILES}
)

target_link_libraries(
  ddprof-lib-test
  GTest::gtest_main
  ${OBJ_FILES}
)


include_directories(
    ../main/cpp
    $ENV{JAVA_HOME}/include
    $ENV{JAVA_HOME}/include/darwin
    $ENV{JAVA_HOME}/include/linux
)

include(GoogleTest)
gtest_discover_tests(ddprof-lib-test)