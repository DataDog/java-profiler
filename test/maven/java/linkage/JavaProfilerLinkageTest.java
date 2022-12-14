package linkage;

import org.junit.jupiter.api.Test;

import one.profiler.JavaProfiler;
import utils.Utils;

public class JavaProfilerLinkageTest {

    @Test
    public void testContextApiLinked() throws Exception {
        JavaProfiler ap = JavaProfiler.getInstance(Utils.getJavaProfilerLib());
        ap.addThread(ap.getNativeThreadId());
        ap.setContext(1, 1);
        ap.clearContext();
    }
}
