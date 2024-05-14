/*
 * Copyright 2021 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LOG_H
#define _LOG_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __GNUC__
#define ATTR_FORMAT __attribute__((format(printf, 1, 2)))
#else
#define ATTR_FORMAT
#endif

#define DD_LOG_LEVELS(X) \
    X(LOG_TRACE, "TRACE") \
    X(LOG_DEBUG, "DEBUG") \
    X(LOG_INFO, "INFO")  \
    X(LOG_WARN, "WARN")  \
    X(LOG_ERROR, "ERROR") \
    X(LOG_NONE, "NONE")

#define X_ENUM(a, b) a,
typedef enum LogLevel : int {
    DD_LOG_LEVELS(X_ENUM) DD_NUM_LOG_LEVELS
} LogLevel;
#undef X_ENUM

class Arguments;

class Log {
  private:
    static FILE* _file;
    static LogLevel _level;

  public:
    #define X_NAME(a, b) b,
        static constexpr const char* LEVEL_NAME[] = {
                DD_LOG_LEVELS(X_NAME)
        };
    #undef X_NAME

    static void open(Arguments& args);
    static void open(const char* file_name, const char* level);
    static void close();

    static void log(LogLevel level, const char* msg, va_list args);

    static void ATTR_FORMAT trace(const char* msg, ...);
    static void ATTR_FORMAT debug(const char* msg, ...);
    static void ATTR_FORMAT info(const char* msg, ...);
    static void ATTR_FORMAT warn(const char* msg, ...);
    static void ATTR_FORMAT error(const char* msg, ...);

    static const char* level() {
        if (_level >= 0 && _level < DD_NUM_LOG_LEVELS) {
            return LEVEL_NAME[_level];
        }
        return "INVALID";
    }
};

#endif // _LOG_H
