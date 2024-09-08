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

#include "log.h"
#include "profiler.h"
#include <string.h>

const char *const Log::LEVEL_NAME[] = {"TRACE", "DEBUG", "INFO",
                                       "WARN",  "ERROR", "NONE"};

FILE *Log::_file = stdout;
LogLevel Log::_level = LOG_NONE;

void Log::open(Arguments &args) {
  open(args._log, args._loglevel);

  if (args._unknown_arg != NULL) {
    warn("Unknown argument: %s", args._unknown_arg);
  }
}

void Log::open(const char *file_name, const char *level) {
  if (_file != stdout && _file != stderr) {
    fclose(_file);
  }

  if (file_name == NULL || strcmp(file_name, "stdout") == 0) {
    _file = stdout;
  } else if (strcmp(file_name, "stderr") == 0) {
    _file = stderr;
  } else if ((_file = fopen(file_name, "w")) == NULL) {
    _file = stdout;
    warn("Could not open log file: %s", file_name);
  }

  LogLevel l = LOG_NONE;
  if (level != NULL) {
    for (int i = LOG_TRACE; i <= LOG_NONE; i++) {
      if (strcasecmp(LEVEL_NAME[i], level) == 0) {
        l = (LogLevel)i;
        break;
      }
    }
  }
  __atomic_store_n(&_level, l, __ATOMIC_RELEASE);
}

void Log::close() {
  if (_file != stdout && _file != stderr) {
    fclose(_file);
    _file = stdout;
  }
}

void Log::log(LogLevel level, const char *msg, va_list args) {
  // DD specific: we don't want to spam stdout/stderr nor JFR with
  //  logs we don't want.
  if (level < _level) {
    return;
  }

  char buf[1024];
  size_t len = vsnprintf(buf, sizeof(buf), msg, args);
  if (len >= sizeof(buf)) {
    len = sizeof(buf) - 1;
    buf[len] = 0;
  }

  // all warnings get logged to the JFR, logging anything else requires config
  // override errors cannot be logged to the JFR because the JFR may not be
  // ready this means all logging we want to be able to find in JFR files must
  // be done at WARN level, and any logging done which prevents creation of the
  // JFR should be done at ERROR level
  if (level == LOG_WARN || (level >= _level && level < LOG_ERROR)) {
    Profiler::instance()->writeLog(level, buf, len);
  }

  // always log errors, but only errors
  if (level == LOG_ERROR) {
    fprintf(_file,
            "{\"@version\":\"1\",\"message\":\"%s\",\"logger_name\":\"java-"
            "profiler\",\"level\":\"%s\"}\n",
            buf, LEVEL_NAME[level]);
    fflush(_file);
  }
}

void Log::trace(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  log(LOG_TRACE, msg, args);
  va_end(args);
}

void Log::debug(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  log(LOG_DEBUG, msg, args);
  va_end(args);
}

void Log::info(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  log(LOG_INFO, msg, args);
  va_end(args);
}

void Log::warn(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  log(LOG_WARN, msg, args);
  va_end(args);
}

void Log::error(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  log(LOG_ERROR, msg, args);
  va_end(args);
}
