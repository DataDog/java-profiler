#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.

# Run the runner's JVM command with separate application and agent API loaders.
# No downloads, allocator changes or shared /tmp cleanup are performed.
# Native gate: test_run_chaos_harness.sh <ddprof.jar> <patched-agent.jar> <evidence-dir> [profiler|profiler+tracer]
set -euo pipefail
ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
python3 - "$ROOT/utils/run-chaos-harness.sh" "$@" <<'PY'
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

assert len(sys.argv) in (2, 5, 6), "supply both real jars, evidence directory and optional config, or no arguments"
source = Path(sys.argv[1]).read_text()
start = source.index('\njava -javaagent:')
end = source.index('\n\nRC=$?', start)
command = source[start:end]

with tempfile.TemporaryDirectory(prefix="chaos launcher ") as tmp:
    root = Path(tmp)
    sources = {
        "api/fixture/api/RuntimeApi.java": """
package fixture.api;
public final class RuntimeApi {
  public static final Object INSTANCE = new Object();
}
""",
        "agent/FixtureAgent.java": """
import java.net.URL;
import java.net.URLClassLoader;
public class FixtureAgent {
  public static void premain(String ignored) throws Exception {
    URL agentJar = FixtureAgent.class.getProtectionDomain().getCodeSource().getLocation();
    URL privateApi = new URL("jar:" + agentJar.toExternalForm() + "!/private/");
    ClassLoader platform = ClassLoader.getSystemClassLoader().getParent();
    try (URLClassLoader isolated = new URLClassLoader(new URL[] {privateApi}, platform)) {
      Class<?> api = Class.forName("fixture.api.RuntimeApi", true, isolated);
      System.getProperties().put("fixture.agent.api", api.getField("INSTANCE").get(null));
    }
  }
}
""",
        "main/com/datadoghq/profiler/chaos/Main.java": """
package com.datadoghq.profiler.chaos;
import fixture.api.RuntimeApi;
import java.util.Arrays;
public class Main {
  public static void main(String[] args) {
    if (RuntimeApi.INSTANCE != System.getProperties().get("fixture.agent.api")) {
      throw new AssertionError("application and agent have different API singletons");
    }
    if (RuntimeApi.class.getClassLoader() != null) {
      throw new AssertionError("API must be bootstrap-defined for the isolated agent parent");
    }
    String[] expected = {"--duration", "7s", "--antagonists", "dump-storm,reapply-context-value"};
    if (!Arrays.equals(args, expected)) throw new AssertionError(Arrays.toString(args));
    if (!Boolean.getBoolean("dd.profiling.enabled")) throw new AssertionError("profiling disabled");
    System.out.println("PASS: shared API singleton; trace=" + System.getProperty("dd.trace.enabled"));
  }
}
""",
    }
    for name, text in sources.items():
        path = root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    for name in ("api", "agent", "main"):
        subprocess.run([
            "javac", "-classpath", str(root / "api-classes"),
            "-d", str(root / f"{name}-classes"),
            *map(str, (root / name).rglob("*.java")),
        ], check=True, capture_output=True, text=True)
    # The agent has a private fallback API copy, like the patched tracer's classdata.
    subprocess.run(["jar", "cf", str(root / "ddprof.jar"), "-C", str(root / "api-classes"), "."], check=True)
    (root / "agent.mf").write_text("Premain-Class: FixtureAgent\n\n")
    shutil.copytree(root / "api-classes", root / "agent-private" / "private")
    subprocess.run([
        "jar", "cfm", str(root / "agent.jar"), str(root / "agent.mf"),
        "-C", str(root / "agent-classes"), ".", "-C", str(root / "agent-private"), ".",
    ], check=True)
    (root / "main.mf").write_text("Main-Class: com.datadoghq.profiler.chaos.Main\n\n")
    subprocess.run([
        "jar", "cfm", str(root / "chaos.jar"), str(root / "main.mf"),
        "-C", str(root / "main-classes"), ".",
    ], check=True)
    for trace in ("false", "true"):
        env = {
            **os.environ,
            "PATCHED_AGENT": str(root / "agent.jar"), "DDPROF_JAR": str(root / "ddprof.jar"),
            "CHAOS_JAR": str(root / "chaos.jar"), "HS_ERR": str(root / "hs_err.log"),
            "ENABLEMENT": f"-Ddd.profiling.enabled=true -Ddd.trace.enabled={trace}",
            "HEAP_MB": "32", "RUNTIME": "7", "ANTAGONISTS": "dump-storm,reapply-context-value",
        }
        result = subprocess.run(["bash", "-c", command], cwd=root, env=env, capture_output=True, text=True)
        assert result.returncode == 0, f"launcher exit {result.returncode}: {result.stdout}\n{result.stderr}"
        assert f"PASS: shared API singleton; trace={trace}" in result.stdout, result.stdout
        print(f"PASS: chaos JVM launcher shares one bootstrap API singleton (trace={trace}, paths with spaces)")
    without_bootstrap = "\n".join(line for line in command.splitlines() if "-Xbootclasspath/a:" not in line)
    app_only = without_bootstrap.replace(
        '-jar "${CHAOS_JAR}"', '-cp "${CHAOS_JAR}:${DDPROF_JAR}" com.datadoghq.profiler.chaos.Main'
    )
    result = subprocess.run(["bash", "-c", app_only], cwd=root, env=env, capture_output=True, text=True)
    assert result.returncode != 0 and "different API singletons" in result.stderr, result.stderr
    print("PASS: app-only classpath negative control detects separate API singletons")

    if len(sys.argv) >= 5:
        ddprof, agent, evidence = map(lambda p: Path(p).resolve(), sys.argv[2:5])
        config = sys.argv[5] if len(sys.argv) == 6 else "disabled"
        assert config in ("disabled", "profiler", "profiler+tracer"), f"unknown native config {config}"
        assert ddprof.is_file() and agent.is_file(), "real ddprof and patched agent jars are required"
        evidence.mkdir(parents=True, exist_ok=True)
        native_tmp = evidence / "tmp"
        native_tmp.mkdir(exist_ok=True)
        probe = evidence / "Main.java"
        probe.write_text("""
package com.datadoghq.profiler.chaos;
import com.datadoghq.profiler.JavaProfiler;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;
public class Main {
  public static void main(String[] args) throws Exception {
    Class<?> agent = Class.forName("datadog.trace.bootstrap.Agent");
    java.lang.reflect.Field loaderField = agent.getDeclaredField("AGENT_CLASSLOADER");
    loaderField.setAccessible(true);
    ClassLoader agentLoader = (ClassLoader) loaderField.get(null);
    if (agentLoader == null) throw new AssertionError("agent loader missing");
    Class<?> agentApi = Class.forName("com.datadoghq.profiler.JavaProfiler", true, agentLoader);
    if (JavaProfiler.class != agentApi || JavaProfiler.class.getClassLoader() != null) {
      throw new AssertionError("application and agent API classes differ or are not bootstrap-defined");
    }
    java.lang.reflect.Field instanceField = agentApi.getDeclaredField("instance");
    instanceField.setAccessible(true);
    Object agentFirstInstance = instanceField.get(null);
    if (Boolean.getBoolean("fixture.expect.agent.first") && agentFirstInstance == null) {
      throw new AssertionError("enabled agent did not initialize its profiler before the application getter");
    }
    JavaProfiler appInstance = JavaProfiler.getInstance();
    Object agentInstance = agentApi.getMethod("getInstance").invoke(null);
    if (appInstance != agentInstance || (agentFirstInstance != null && appInstance != agentFirstInstance)) {
      throw new AssertionError("native singleton instances differ");
    }
    String version = appInstance.getVersion();
    if (version == null || version.isEmpty()) throw new AssertionError("native version unavailable");
    long libraries;
    // DdprofLibraryLoader passes TempLocationManager's nested scratch directory to the API loader.
    // Walk the owned tmp tree, not just its root; LibraryLoader retains the extracted file until exit.
    try (Stream<java.nio.file.Path> files = Files.walk(Paths.get(System.getProperty("java.io.tmpdir")))) {
      libraries = files.filter(Files::isRegularFile)
          .filter(p -> p.getFileName().toString().startsWith("libjavaProfiler"))
          .peek(p -> System.out.println("extractedNativeArtifact=" + p.toAbsolutePath())).count();
    }
    if (libraries != 1) throw new AssertionError("expected one extracted native library, found " + libraries);
    System.out.println("PASS: real bootstrap appApi==agentApi; shared native singleton; init0/getVersion="
        + version + "; extractedNativeLibraries=" + libraries + "; agentFirst=" + (agentFirstInstance != null));
  }
}
""")
        subprocess.run([
            "javac", "-classpath", str(ddprof), "-d", str(evidence / "classes"), str(probe),
        ], check=True, capture_output=True, text=True)
        native_jar = evidence / "native-probe.jar"
        subprocess.run([
            "jar", "cfm", str(native_jar), str(root / "main.mf"),
            "-C", str(evidence / "classes"), ".",
        ], check=True)
        settings = {
            "PATCHED_AGENT": str(agent), "DDPROF_JAR": str(ddprof), "CHAOS_JAR": str(native_jar),
            "HS_ERR": str(evidence / "hs_err.log"), "HEAP_MB": "128", "RUNTIME": "7",
            "ANTAGONISTS": "dump-storm,reapply-context-value",
            "ENABLEMENT": "-Ddd.profiling.enabled=false -Ddd.trace.enabled=false "
                "-Ddd.instrumentation.telemetry.enabled=false -Ddd.remote_config.enabled=false "
                "-Ddd.appsec.enabled=false",
        }
        # Quote owned tmp paths separately from the runner's word-split ENABLEMENT flags.
        native_command = command.replace(
            'java -javaagent:', 'java -Djava.io.tmpdir="${NATIVE_TMP}" -Ddd.profiling.tempdir="${NATIVE_TMP}" -javaagent:'
        )
        settings["NATIVE_TMP"] = str(native_tmp)
        if config != "disabled":
            settings["ENABLEMENT"] = "-Ddd.profiling.enabled=true -Ddd.trace.enabled=" + (
                "true" if config == "profiler+tracer" else "false"
            )
            settings["HEAP_MB"] = "3072"
            native_command = native_command.replace("java -Djava.io.tmpdir=", "java -Dfixture.expect.agent.first=true -Djava.io.tmpdir=")
        receipt = {
            "config": config, "runnerSha256": hashlib.sha256(source.encode()).hexdigest(),
            "command": ["bash", "-c", native_command], "environmentOverrides": settings,
            "cwd": str(evidence),
            "jdk": subprocess.run(["java", "-version"], capture_output=True, text=True, check=True).stderr,
            "sha256": {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in (ddprof, agent, probe, native_jar)},
            "scope": "Actual native extraction/System.load/init0 with agent and bootstrap append; no chaos workload claim",
            "state": "prepared",
        }
        receipt_path = evidence / "receipt.json"
        receipt_path.write_text(json.dumps(receipt, indent=2) + "\n")
        result = subprocess.run(
            ["bash", "-c", native_command], cwd=evidence, env={**os.environ, **settings}, capture_output=True, text=True
        )
        (evidence / "stdout.log").write_text(result.stdout)
        (evidence / "stderr.log").write_text(result.stderr)
        receipt.update(state="completed", exitStatus=result.returncode)
        receipt_path.write_text(json.dumps(receipt, indent=2) + "\n")
        assert result.returncode == 0, f"native launcher exit {result.returncode}; see {evidence}"
        assert "PASS: real bootstrap appApi==agentApi; shared native singleton; init0/getVersion=" in result.stdout, result.stdout
        assert not (evidence / "hs_err.log").exists(), "unexpected native crash log"
        print(result.stdout.strip())
PY
