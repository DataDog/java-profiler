#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Inert XML fixtures for the real-VM CI execution gate."""
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET

SCRIPT = Path(__file__).resolve().parents[1] / "assert_vm_qualification.py"
ROOT = SCRIPT.parents[2]
spec = importlib.util.spec_from_file_location("assert_vm_qualification", SCRIPT)
qualification = importlib.util.module_from_spec(spec)
spec.loader.exec_module(qualification)


class AssertVmQualificationTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.results = Path(self.temp.name)

    def write_results(self, vm):
        suite = ET.Element("testsuite")
        cases = []
        for cls, method in qualification.EXPECTED_METHODS[vm].items():
            cases.append(ET.SubElement(suite, "testcase", {
                "classname": qualification.PREFIX + cls, "name": method + "()"}))
        return suite, cases

    def save(self, suite):
        ET.ElementTree(suite).write(self.results / "TEST-qualification.xml")

    def invoke(self, vm, success):
        result = subprocess.run(
            [sys.executable, str(SCRIPT), "--vm", vm, "--results", str(self.results)],
            capture_output=True, text=True)
        self.assertEqual(result.returncode, 0 if success else 1, result.stdout + result.stderr)
        return result

    def test_every_vm_requires_its_actual_source_methods(self):
        for vm in qualification.EXPECTED_METHODS:
            with self.subTest(vm=vm):
                suite, cases = self.write_results(vm)
                self.save(suite)
                result = self.invoke(vm, True)
                self.assertIn("3 intended " + vm + " methods passed without skips", result.stdout)
                for cls, method in qualification.EXPECTED_METHODS[vm].items():
                    source = (ROOT / "ddprof-test/src/test/java/com/datadoghq/profiler/wallclock" /
                              (cls + ".java")).read_text()
                    self.assertIn("public void " + method + "()", source)

    def test_each_missing_method_fails_despite_other_successes(self):
        for vm in qualification.EXPECTED_METHODS:
            for missing in range(len(qualification.EXPECTED_METHODS[vm])):
                with self.subTest(vm=vm, missing=missing):
                    suite, cases = self.write_results(vm)
                    suite.remove(cases[missing])
                    self.save(suite)
                    result = self.invoke(vm, False)
                    self.assertIn("Missing qualification methods", result.stderr)
                    self.assertIn(cases[missing].get("name")[:-2], result.stderr)

    def test_each_skipped_failed_or_errored_method_fails(self):
        for vm in qualification.EXPECTED_METHODS:
            for rejected in range(len(qualification.EXPECTED_METHODS[vm])):
                for tag in ("skipped", "failure", "error"):
                    with self.subTest(vm=vm, rejected=rejected, tag=tag):
                        suite, cases = self.write_results(vm)
                        ET.SubElement(cases[rejected], tag)
                        self.save(suite)
                        self.assertIn("did not pass without skips", self.invoke(vm, False).stderr)

    def test_zero_cases_missing_results_and_unrelated_cases_fail(self):
        self.assertIn("Missing qualification methods", self.invoke("hotspot", False).stderr)
        suite = ET.Element("testsuite", tests="100", skipped="0")
        ET.SubElement(suite, "testcase", classname="UnrelatedTest", name="passes()")
        self.save(suite)
        self.assertIn("Missing qualification methods", self.invoke("openj9", False).stderr)

    def test_malformed_or_unreadable_xml_fails(self):
        path = self.results / "TEST-qualification.xml"
        path.write_text("<broken")
        self.assertIn("Real-VM qualification failed", self.invoke("hotspot", False).stderr)
        path.unlink()
        path.mkdir()
        self.assertIn("Real-VM qualification failed", self.invoke("hotspot", False).stderr)

    def test_failure_is_not_hidden_by_duplicate_success(self):
        suite, cases = self.write_results("hotspot")
        failed = ET.SubElement(suite, "testcase", cases[0].attrib)
        ET.SubElement(failed, "failure")
        self.save(suite)
        self.invoke("hotspot", False)

    def test_unavailable_delegated_extension_is_not_counted_as_a_pass(self):
        suite, cases = self.write_results("hotspot")
        delegated = next(case for case in cases if case.get("classname") == qualification.DELEGATED_METHOD[0])
        ET.SubElement(delegated, "skipped")
        ET.SubElement(suite, "system-out").text = qualification.EXTENSION_UNAVAILABLE
        self.save(suite)
        result = self.invoke("hotspot", True)
        self.assertIn("2 intended hotspot methods passed without skips", result.stdout)
        self.assertIn("Delegated JVM-stack qualification deferred", result.stdout)
        self.assertNotIn("3 intended", result.stdout)
        source = (ROOT / "ddprof-test/src/test/java/com/datadoghq/profiler/wallclock" /
                  "HotSpotDelegatedProducerLifecycleTest.java").read_text()
        self.assertIn(qualification.EXTENSION_UNAVAILABLE, source)
        self.assertIn("System.out.println(EXTENSION_UNAVAILABLE)", source)

    def test_unavailable_marker_never_excuses_failures_or_errors(self):
        for vm in qualification.EXPECTED_METHODS:
            for rejected in range(len(qualification.EXPECTED_METHODS[vm])):
                for tag in ("failure", "error"):
                    with self.subTest(vm=vm, rejected=rejected, tag=tag):
                        suite, cases = self.write_results(vm)
                        ET.SubElement(cases[rejected], "skipped")
                        ET.SubElement(cases[rejected], tag)
                        ET.SubElement(suite, "system-out").text = qualification.EXTENSION_UNAVAILABLE
                        self.save(suite)
                        self.invoke(vm, False)

    def test_unavailable_marker_never_excuses_other_skips(self):
        for vm in qualification.EXPECTED_METHODS:
            for rejected in range(len(qualification.EXPECTED_METHODS[vm])):
                suite, cases = self.write_results(vm)
                if cases[rejected].get("classname") == qualification.DELEGATED_METHOD[0]:
                    continue
                with self.subTest(vm=vm, rejected=rejected):
                    ET.SubElement(cases[rejected], "skipped")
                    ET.SubElement(suite, "system-out").text = qualification.EXTENSION_UNAVAILABLE
                    self.save(suite)
                    self.invoke(vm, False)

    def test_unavailable_reason_must_be_in_the_delegated_result_file(self):
        suite, cases = self.write_results("hotspot")
        delegated = next(case for case in cases if case.get("classname") == qualification.DELEGATED_METHOD[0])
        ET.SubElement(delegated, "skipped")
        self.save(suite)
        unrelated = ET.Element("testsuite")
        ET.SubElement(unrelated, "system-out").text = qualification.EXTENSION_UNAVAILABLE
        ET.ElementTree(unrelated).write(self.results / "TEST-unrelated.xml")
        self.invoke("hotspot", False)

    def test_workflow_enables_and_checks_explicit_applicable_cells(self):
        workflow = (ROOT / ".github/workflows/test_workflow.yml").read_text()
        job = workflow.split("  qualify-real-vm:\n", 1)[1]
        for text in ("expected_vm: hotspot", 'java_version: "25"', "expected_vm: openj9",
                     'java_version: "17-j9"', "DDPROF_EXPECTED_VM: ${{ matrix.expected_vm }}",
                     "--tests '*ProducerLifecycleTest'", "--tests '*RealVmThreadClassifierTest'",
                     'assert_vm_qualification.py --vm "$DDPROF_EXPECTED_VM"',
                     "--results ddprof-test/build/test-results/testDebug", "--rerun-tasks",
                     "if: always()", "ddprof-test/build/test-results/"):
            self.assertIn(text, job)


if __name__ == "__main__":
    unittest.main()
