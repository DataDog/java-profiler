// Copyright 2026, Datadog, Inc

// probe_event_types_fixture.java - deterministic recording for
// probe_event_types_real_test.sh, generated at test time.
//
// Run with: jbang --java 25 probe_event_types_fixture.java <output.jfr>
//
// jbang executes a single self-contained .java file, so the event classes are
// nested and take their recorded names from @Name. The fixture registers two
// of the types probe-event-types.jfrs tracks - jdk.ExecutionSample (2 events)
// and datadog.ExecutionSample (3 events) - via @Name overrides; the other
// four tracked types are never defined, so the recording exercises both the
// present and the absent branch of the probe. Exact counts pin the variable
// interpolation in the HAS lines.

import jdk.jfr.*;

public class probe_event_types_fixture {

    @Name("jdk.ExecutionSample")
    static class JdkExecutionSample extends Event {}

    @Name("datadog.ExecutionSample")
    static class DatadogExecutionSample extends Event {}

    public static void main(String... args) throws Exception {
        Recording recording = new Recording();
        recording.enable(JdkExecutionSample.class);
        recording.enable(DatadogExecutionSample.class);
        recording.start();
        for (int i = 0; i < 2; i++) {
            new JdkExecutionSample().commit();
        }
        for (int i = 0; i < 3; i++) {
            new DatadogExecutionSample().commit();
        }
        recording.stop();
        recording.dump(java.nio.file.Path.of(args[0]));
        recording.close();
    }
}
