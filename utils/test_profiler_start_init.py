#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
"""Compile Profiler::start's exact dispatch/init block, not Linux engine startup.
Neither the production predicate nor its initialization-failure return is copied.
"""

import hashlib
import json
import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "ddprof-lib/src/main/cpp/profiler.cpp"


def dispatch_init_block(source):
    """Select the contiguous production block, checking its startup ordering."""
    start = source.index("Error Profiler::start(Arguments &args, bool reset)")
    end = source.index("Error Profiler::stop(", start)
    startup = source[start:end]
    first = startup.index("  _cpu_engine = selectCpuEngine(args);")
    last = startup.index("  const char *filter =", first)
    block = startup[first:last]
    if block.count("VM::initializeRequestStackTrace()") != 1:
        raise AssertionError("expected one initializer call in the dispatch block")
    if not last < startup.index("_cpu_engine->start(args)"):
        raise AssertionError("CPU engine launch must follow initialization")
    if not last < startup.index("_wall_engine->start(args)"):
        raise AssertionError("wall engine launch must follow initialization")
    return block


# Only boundaries are instrumented: selection, initialization and engine launch.
# The region between selection and launch is inserted verbatim from profiler.cpp.
HARNESS = r'''
#include <iostream>
#include <string>

struct Arguments { bool _jvmtistacks; };
struct Error {
  std::string message;
  explicit Error(const char* text = "") : message(text) {}
  explicit operator bool() const { return !message.empty(); }
};
struct Engine {
  const char* name;
  int launches = 0;
  void start() { ++launches; }
};
static std::string trace;
static constexpr int EM_CPU = 1;
static constexpr int EM_WALL = 2;
struct VM {
  inline static int calls = 0;
  inline static bool result = true;
  static bool initializeRequestStackTrace() {
    trace += "init,";
    ++calls;
    return result;
  }
};
struct DispatchHarness {
  Engine ctimer_jvmti{"CTimerJvmti"};
  Engine itimer_jvmti{"ITimerJvmti"};
  Engine wall_jvmti_engine{"WallClockJvmti"};
  Engine asgct{"ASGCT"};
  Engine noop_engine{"None"};
  Engine* _cpu_engine = nullptr;
  Engine* _wall_engine = nullptr;
  int _event_mask;
  std::string selected;
  Engine* selectCpuEngine(Arguments&) {
    trace += "select_cpu,";
    if (!(_event_mask & EM_CPU)) return &noop_engine;
    if (selected == "CTimerJvmti") return &ctimer_jvmti;
    if (selected == "ITimerJvmti") return &itimer_jvmti;
    return &asgct;
  }
  Engine* selectWallEngine(Arguments&) {
    trace += "select_wall,";
    return (_event_mask & EM_WALL) ? &wall_jvmti_engine : &noop_engine;
  }
  Error start(Arguments& args) {
/* PRODUCTION_DISPATCH_INIT_BLOCK */
    if (_event_mask & EM_CPU) {
      trace += "cpu_launch,";
      _cpu_engine->start();
    }
    if (_event_mask & EM_WALL) {
      trace += "wall_launch,";
      _wall_engine->start();
    }
    return Error();
  }
};
int main(int argc, char** argv) {
  if (argc != 6) return 2;
  DispatchHarness harness;
  harness.selected = argv[1];
  Arguments args{std::stoi(argv[2]) != 0};
  harness._event_mask = std::stoi(argv[3]);
  VM::result = std::stoi(argv[4]) != 0;
  for (int i = 0; i < std::stoi(argv[5]); ++i) {
    trace.clear();
    Error error = harness.start(args);
    std::cout << VM::calls << '\t' << harness._cpu_engine->launches << '\t'
              << harness._wall_engine->launches << '\t'
              << harness._cpu_engine->name << '\t'
              << harness._wall_engine->name << '\t'
              << trace << '\t' << error.message << '\n';
  }
}
'''


class ProfilerStartInitDispatchTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        source_path = Path(os.environ.get("DDPROF_START_INIT_SOURCE", SOURCE))
        source = source_path.read_text()
        block = dispatch_init_block(source)
        cls.directory = tempfile.TemporaryDirectory(prefix="profiler-start-init-")
        cls.addClassCleanup(cls.directory.cleanup)
        directory = Path(cls.directory.name)
        harness = HARNESS.replace("/* PRODUCTION_DISPATCH_INIT_BLOCK */", block)
        cpp = directory / "profiler_start_init.cpp"
        cpp.write_text(harness)
        cls.executable = directory / "profiler_start_init"
        command = shlex.split(os.environ.get("CXX", "c++")) + [
            "-std=c++17", "-Wall", "-Wextra", "-Werror", str(cpp), "-o", str(cls.executable)]
        subprocess.run(command, check=True, capture_output=True, text=True)
        # Optional retained evidence, including the exact generated translation unit.
        if "DDPROF_START_INIT_EVIDENCE" in os.environ:
            evidence = Path(os.environ["DDPROF_START_INIT_EVIDENCE"])
            evidence.mkdir(parents=True, exist_ok=True)
            (evidence / cpp.name).write_text(harness)
            (evidence / "source-binding.json").write_text(json.dumps({
                "source": str(source_path),
                "sourceSha256": hashlib.sha256(source.encode()).hexdigest(),
                "dispatchBlockSha256": hashlib.sha256(block.encode()).hexdigest(),
                "harnessSha256": hashlib.sha256(harness.encode()).hexdigest(),
                "compileCommand": command,
                "boundary": "Exact dispatch/init block only; not Linux runtime engine startup",
            }, indent=2) + "\n")

    def run_dispatch(self, engine, *, opted_in=True, events=1, init_ok=True,
                     sessions=1):
        result = subprocess.run([
            str(self.executable), engine, str(int(opted_in)), str(events),
            str(int(init_ok)), str(sessions)],
            check=True, capture_output=True, text=True)
        rows = []
        for line in result.stdout.splitlines():
            calls, cpu, wall, cpu_name, wall_name, trace, error = line.split("\t")
            rows.append(dict(calls=int(calls), cpu_launches=int(cpu),
                             wall_launches=int(wall), cpu_name=cpu_name,
                             wall_name=wall_name, trace=trace, error=error))
        self.assertEqual(sessions, len(rows))
        return rows

    def expect_cpu_only(self, engine):
        row, = self.run_dispatch(engine)
        self.assertEqual(engine, row["cpu_name"])
        self.assertEqual("None", row["wall_name"])
        self.assertEqual(1, row["calls"])
        self.assertEqual(1, row["cpu_launches"])
        self.assertEqual(0, row["wall_launches"])
        self.assertEqual("select_cpu,select_wall,init,cpu_launch,", row["trace"])
        self.assertEqual("", row["error"])

    def expect_initializer_error(self, engine):
        row, = self.run_dispatch(engine, init_ok=False)
        self.assertEqual(engine, row["cpu_name"])
        self.assertEqual("None", row["wall_name"])
        self.assertEqual(1, row["calls"])
        self.assertEqual(0, row["cpu_launches"])
        self.assertEqual(0, row["wall_launches"])
        self.assertEqual("select_cpu,select_wall,init,", row["trace"])
        self.assertEqual("Failed to initialize JVM delegated stack traces", row["error"])

    def test_ctimer_jvmti_cpu_only_initializes_before_launch(self):
        self.expect_cpu_only("CTimerJvmti")

    def test_itimer_jvmti_cpu_only_initializes_before_launch(self):
        self.expect_cpu_only("ITimerJvmti")

    def test_ctimer_jvmti_initializer_error_prevents_launch(self):
        self.expect_initializer_error("CTimerJvmti")

    def test_itimer_jvmti_initializer_error_prevents_launch(self):
        self.expect_initializer_error("ITimerJvmti")

    def test_cpu_only_retained_worker_restart_initializes_each_session(self):
        for engine in ("CTimerJvmti", "ITimerJvmti"):
            with self.subTest(engine=engine):
                rows = self.run_dispatch(engine, sessions=2)
                self.assertEqual([1, 2], [row["calls"] for row in rows])
                self.assertEqual([1, 2], [row["cpu_launches"] for row in rows])
                self.assertTrue(all(row["trace"] == "select_cpu,select_wall,init,cpu_launch,"
                                    for row in rows))

    def test_unselected_or_non_opted_cpu_does_not_initialize(self):
        for engine, opted_in in (("ASGCT", True), ("CTimerJvmti", False),
                                 ("ITimerJvmti", False)):
            with self.subTest(engine=engine, opted_in=opted_in):
                row, = self.run_dispatch(engine, opted_in=opted_in)
                self.assertEqual(0, row["calls"])
                self.assertEqual(1, row["cpu_launches"])
                self.assertEqual("", row["error"])

    def test_wall_only_still_initializes_before_launch(self):
        row, = self.run_dispatch("ASGCT", events=2)
        self.assertEqual(1, row["calls"])
        self.assertEqual(0, row["cpu_launches"])
        self.assertEqual(1, row["wall_launches"])
        self.assertEqual("select_cpu,select_wall,init,wall_launch,", row["trace"])

    def test_no_active_event_does_not_initialize(self):
        row, = self.run_dispatch("CTimerJvmti", events=0)
        self.assertEqual(0, row["calls"])
        self.assertEqual(0, row["cpu_launches"])
        self.assertEqual(0, row["wall_launches"])


if __name__ == "__main__":
    unittest.main()
