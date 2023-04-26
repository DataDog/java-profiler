# Unless explicitly stated otherwise all files in this repository are licensed under the Apache
# License Version 2.0. This product includes software developed at Datadog
# (https://www.datadoghq.com/). Copyright 2021-Present Datadog, Inc.

set(SAN_FLAGS "-fsanitize=undefined -fsanitize=float-divide-by-zero -fno-sanitize-recover")
set(ASAN_FLAGS "-fsanitize=address")
set(TSAN_FLAGS "-fsanitize=thread")
set(STACK_FLAGS "-fstack-protector-all")

list(APPEND CMAKE_CONFIGURATION_TYPES SanitizedDebug ThreadSanitizedDebug)
message(STATUS "Adding  SanitizedDebug, ThreadSanitizedDebug as build types")

# Add flags for sanitized debug (asan)
set(CMAKE_CXX_FLAGS_SANITIZEDDEBUG
    "${SAN_FLAGS} ${ASAN_FLAGS} ${STACK_FLAGS}"
    CACHE STRING "Flags used by the C++ compiler during sanitized builds." FORCE)
set(CMAKE_C_FLAGS_SANITIZEDDEBUG
    "${SAN_FLAGS} ${ASAN_FLAGS} ${STACK_FLAGS}"
    CACHE STRING "Flags used by the C compiler during sanitized builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_SANITIZEDDEBUG
    ""
    CACHE STRING "Flags used for linking binaries during sanitized builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_SANITIZEDDEBUG
    ""
    CACHE STRING "Flags used by the shared libraries linker during sanitized builds." FORCE)

# Add flags for thread-sanized debug
set(CMAKE_CXX_FLAGS_THREADSANITIZEDDEBUG
    "${SAN_FLAGS} ${TSAN_FLAGS} ${STACK_FLAGS}"
    CACHE STRING "Flags used by the C++ compiler during sanitized builds." FORCE)
set(CMAKE_C_FLAGS_THREADSANITIZEDDEBUG
    "${SAN_FLAGS} ${TSAN_FLAGS} ${STACK_FLAGS}"
    CACHE STRING "Flags used by the C compiler during sanitized builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_THREADSANITIZEDDEBUG
    ""
    CACHE STRING "Flags used for linking binaries during sanitized builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_THREADSANITIZEDDEBUG
    ""
    CACHE STRING "Flags used by the shared libraries linker during sanitized builds." FORCE)

string(REPLACE ";" " " LD_FLAGS_STR "${LD_FLAGS}")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_EXE_LINKER_FLAGS_SANITIZEDDEBUG
      "${CMAKE_EXE_LINKER_FLAGS_SANITIZEDDEBUG} -static-libasan -static-libubsan -static-liblsan")
  set(CMAKE_SHARED_LINKER_FLAGS_SANITIZEDDEBUG
      "${CMAKE_SHARED_LINKER_FLAGS_SANITIZEDDEBUG} -static-libasan -static-libubsan -static-liblsan")
  set(CMAKE_EXE_LINKER_FLAGS_THREADSANITIZEDDEBUG
      "${CMAKE_EXE_LINKER_FLAGS_THREADSANITIZEDDEBUG} -static-libtsan -static-libubsan")
  set(CMAKE_SHARED_LINKER_FLAGS_THREADSANITIZEDDEBUG
      "${CMAKE_SHARED_LINKER_FLAGS_THREADSANITIZEDDEBUG} -static-libtsan -static-libubsan")
endif()

mark_as_advanced(
  CMAKE_CXX_FLAGS_SANITIZEDDEBUG
  CMAKE_C_FLAGS_SANITIZEDDEBUG
  CMAKE_EXE_LINKER_FLAGS_SANITIZEDDEBUG
  CMAKE_SHARED_LINKER_FLAGS_SANITIZEDDEBUG
  CMAKE_CXX_FLAGS_THREADSANITIZEDDEBUG
  CMAKE_C_FLAGS_THREADSANITIZEDDEBUG
  CMAKE_EXE_LINKER_FLAGS_THREADSANITIZEDDEBUG
  CMAKE_SHARED_LINKER_FLAGS_THREADSANITIZEDDEBUG)
