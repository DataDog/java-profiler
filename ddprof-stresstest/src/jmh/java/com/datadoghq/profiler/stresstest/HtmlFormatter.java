package com.datadoghq.profiler.stresstest;

import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.infra.BenchmarkParams;
import org.openjdk.jmh.results.Result;
import org.openjdk.jmh.results.RunResult;

import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Collection;
import java.util.SortedSet;
import java.util.TreeSet;

import static com.datadoghq.profiler.stresstest.Main.SCENARIOS_PACKAGE;

public class HtmlFormatter {

    private final Collection<RunResult> results;
    private final PrintStream out;
    private final String delimiter = "~";
    private final Mode mode;

    public HtmlFormatter(Collection<RunResult> results, Mode mode) throws IOException {
        this.results = results;
        this.mode = mode;
        Path html = Paths.get(System.getProperty("user.dir")).resolve("jmh-result.html");
        Files.deleteIfExists(html);
        Files.createFile(html);
        this.out = new PrintStream(html.toFile());
    }

    private void printHeader(SortedSet<String> params) {
        out.print("<thead><tr>");
        out.print("<th>Scenario</th>");
        out.print("<th>Metric</th>");
        out.print("<th>Score</th>");
        for (String k : params) {
            out.print("<th>");
            out.print(k);
            out.print("</th>");
        }
        out.print("</tr></thead>");
    }

    private void startHtml() {
        out.print("<html><body>");
    }

    private void endHtml() {
        out.print("</body></html>");
    }

    private void startTable() {
        out.print("<table>");
    }

    private void endTable() {
        out.print("</table>");
    }

    private void startTableBody() {
        out.print("<tbody>");
    }

    private void endTableBody() {
        out.print("</tbody>");
    }

    private void printEnvironment() {
        out.print("<h2>Setup</h2>");
        startTable();
        startTableBody();
        out.print("<tr><td>Commit</td><td>" + System.getenv("TEST_COMMIT") + "</td></tr>");
        out.print("<tr><td>LibC</td><td>" + System.getenv("LIBC") + "</td></tr>");
        out.print("<tr><td>JVM Vendor</td><td>" + System.getProperty("java.vm.vendor") + "</td></tr>");
        out.print("<tr><td>Version</td><td>" + System.getProperty("java.version") + "</td></tr>");
        out.print("<tr><td>Operating System</td><td>" + System.getProperty("os.name") +"</td></tr>");
        out.print("<tr><td>Architecture</td><td>" + System.getProperty("os.arch") + "</td></tr>");
        endTableBody();
        endTable();
    }

    public void print() {
        startHtml();
        out.print("<h2>Stress Tests</h2>");
        printEnvironment();
        SortedSet<String> params = new TreeSet<>();
        for (RunResult res : results) {
            params.addAll(res.getParams().getParamsKeys());
        }
        out.print("<h1>Results</h1>");
        startTable();
        printHeader(params);
        startTableBody();
        for (RunResult result : results) {
            BenchmarkParams benchParams = result.getParams();
            Result timing = result.getPrimaryResult();
            String benchmarkName = benchParams.getBenchmark().replace(SCENARIOS_PACKAGE, "");
            printRow(benchmarkName, mode.shortLabel(), benchParams, params, timing);
            for (String label : result.getSecondaryResults().keySet()) {
                Result metric = result.getSecondaryResults().get(label);
                printRow(benchmarkName, metric.getLabel(), benchParams, params, metric);
            }
        }
        endTableBody();
        endTable();
        endHtml();
    }

    private void printRow(String scenario, String metric, BenchmarkParams benchmarkParams, SortedSet<String> params, Result result) {
        out.print("<td>");
        out.print(scenario);
        out.print("</td>");
        out.print("<td>");
        out.print(metric);
        out.print("</td>");
        out.print("<td>");
        out.print(emit(result.getScore()));
        out.print("</td>");
        for (String p : params) {
            out.print("<td>");
            String v = benchmarkParams.getParam(p);
            if (v != null) {
                out.print(emit(v));
            }
            out.print("</td>");
        }
        out.print("</tr>");
    }

    private String emit(String v) {
        return v;
    }

    private String emit(int i) {
        return emit(String.format("%d", i));
    }

    private String emit(long l) {
        return emit(String.format("%d", l));
    }

    private String emit(double d) {
        return emit(String.format("%f", d));
    }
}
