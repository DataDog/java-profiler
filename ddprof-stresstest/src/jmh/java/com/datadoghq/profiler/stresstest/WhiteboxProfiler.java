package com.datadoghq.profiler.stresstest;

import com.datadoghq.profiler.JavaProfiler;
import org.openjdk.jmh.infra.BenchmarkParams;
import org.openjdk.jmh.infra.IterationParams;
import org.openjdk.jmh.profile.InternalProfiler;
import org.openjdk.jmh.results.AggregationPolicy;
import org.openjdk.jmh.results.IterationResult;
import org.openjdk.jmh.results.Result;
import org.openjdk.jmh.results.ScalarResult;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Map;

public class WhiteboxProfiler implements InternalProfiler {

    private Path jfr;

    @Override
    public String getDescription() {
        return "ddprof-whitebox";
    }

    @Override
    public void beforeIteration(BenchmarkParams benchmarkParams, IterationParams iterationParams) {
        try {
            jfr = Files.createTempFile(benchmarkParams.getBenchmark() + System.currentTimeMillis(), ".jfr");
            String command = "start," + benchmarkParams.getParam("command")
                    .replace(':', ';') // simplify result parsing
                    + ",jfr,file=" + jfr.toAbsolutePath();
            JavaProfiler.getInstance().execute(command);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Collection<? extends Result> afterIteration(BenchmarkParams benchmarkParams, IterationParams iterationParams, IterationResult result) {
        // TODO unit encoded in counter name for now, so results are effectively dimensionless
        try {
            JavaProfiler.getInstance().stop();
            long fileSize = Files.size(jfr);
            Files.deleteIfExists(jfr);
            List<ScalarResult> results = new ArrayList<>();
            results.add(new ScalarResult("jfr_filesize_bytes", fileSize, "", AggregationPolicy.MAX));
            for (Map.Entry<String, Long> counter : JavaProfiler.getInstance().getDebugCounters().entrySet()) {
                results.add(new ScalarResult(counter.getKey(), counter.getValue(), "", AggregationPolicy.MAX));
            }
            return results;
        } catch (IOException e) {
            e.printStackTrace();
            return Collections.emptyList();
        }
    }
}
