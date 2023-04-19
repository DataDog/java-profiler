package com.datadoghq.profiler.stresstest;

import com.datadoghq.profiler.JavaProfiler;
import org.openjdk.jmh.infra.BenchmarkParams;
import org.openjdk.jmh.profile.ExternalProfiler;
import org.openjdk.jmh.results.AggregationPolicy;
import org.openjdk.jmh.results.BenchmarkResult;
import org.openjdk.jmh.results.Result;
import org.openjdk.jmh.results.ScalarResult;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Map;

public class WhiteboxProfiler implements ExternalProfiler {

    private Path jfr;
    @Override
    public Collection<String> addJVMInvokeOptions(BenchmarkParams benchmarkParams) {
        return Collections.emptyList();
    }

    @Override
    public Collection<String> addJVMOptions(BenchmarkParams benchmarkParams) {
        return Collections.emptyList();
    }

    @Override
    public void beforeTrial(BenchmarkParams benchmarkParams) {
        try {
            jfr = Files.createTempFile(benchmarkParams.getBenchmark() + System.currentTimeMillis(), ".jfr");
            String command = "start," + benchmarkParams.getParam("command") + ",jfr,file=" + jfr.toAbsolutePath();
            JavaProfiler.getInstance().execute(command);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Collection<? extends Result> afterTrial(BenchmarkResult br, long pid, File stdOut, File stdErr) {
        // TODO unit encoded in counter name for now, so results are effectively dimensionless
        try {
            Map<String, Long> counters = JavaProfiler.getInstance().getDebugCounters();
            JavaProfiler.getInstance().stop();
            long fileSize = Files.size(jfr);
            Files.deleteIfExists(jfr);
            List<ScalarResult> results = new ArrayList<>();
            results.add(new ScalarResult("jfr:filesize:bytes", fileSize, "", AggregationPolicy.MAX));
            for (Map.Entry<String, Long> counter : counters.entrySet()) {
                results.add(new ScalarResult(counter.getKey(), counter.getValue(), "", AggregationPolicy.MAX));
            }
            return results;
        } catch (IOException e) {
            e.printStackTrace();
            return Collections.emptyList();
        }
    }

    @Override
    public boolean allowPrintOut() {
        return true;
    }

    @Override
    public boolean allowPrintErr() {
        return true;
    }

    @Override
    public String getDescription() {
        return "ddprof-whitebox";
    }
}
