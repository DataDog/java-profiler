package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItemCollection;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies that nativesocket profiling survives a stop/restart cycle.
 * Events must be recorded in the second profiling session, confirming
 * that lifecycle management (hook install/uninstall/reinstall) is correct.
 */
public class NativeSocketRestartTest extends NativeSocketTestBase {

    @RetryingTest(3)
    public void testNativeSocketProfilerRestart() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        // First session: framework already started the profiler in @BeforeEach.
        doTcpTransfer(4096, 64);
        stopProfiler();

        // Second session: start manually with a fresh JFR file.
        Path jfr2 = Files.createTempFile(Paths.get("/tmp/recordings"), "NativeSocketRestartTest_restart", ".jfr");
        try {
            profiler.execute("start,natsock=100us,jfr,file=" + jfr2.toAbsolutePath());

            doTcpTransfer(4096, 64);

            profiler.stop();

            IItemCollection events = verifyEvents(jfr2, "datadog.NativeSocketEvent", true);
            assertTrue(events.hasItems(),
                    "NativeSocketEvent events must be recorded in the second profiling session");
        } finally {
            Files.deleteIfExists(jfr2);
        }
    }
}
