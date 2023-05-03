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

public class HtmlCommentFormatter extends AbstractFormatter {

    private final Collection<RunResult> results;

    private final String delimiter = "~";
    private final Mode mode;

    public HtmlCommentFormatter(Collection<RunResult> results, Mode mode) throws IOException {
        super(Paths.get(System.getProperty("user.dir")).resolve("jmh-comment.html"));
        this.results = results;
        this.mode = mode;
    }

    private void startHtml() {
        out.print("<html><body>");
    }

    private void endHtml() {
        out.print("</body></html>");
    }

    private void printEnvironment() {
        out.println("<table width='100%'>");
        out.println("<thead><tr><th>Commit</th><th>LibC</th><th>JVM Vendor</th><th>Version</th><th>Operating System</th><th>Architecture</th></tr></thead>");
        out.println("<tbody>");
        out.print("<tr>");
        out.print("<td>" + System.getenv("TEST_COMMIT") + "</td>");
        out.print("<td>" + System.getenv("LIBC") + "</td>");
        out.print("<td>" + System.getProperty("java.vm.vendor") + "</td>");
        out.print("<td>" + System.getProperty("java.version") + "</td>");
        out.print("<td>" + System.getProperty("os.name") +"</td>");
        out.print("<td>" + System.getProperty("os.arch") + "</td>");
        out.println("</tr>");
        out.println("</tbody></table>");
    }

    public void print() {
        startHtml();
        printEnvironment();
        SortedSet<String> params = new TreeSet<>();
        for (RunResult res : results) {
            params.addAll(res.getParams().getParamsKeys());
        }
        out.println("<h3>Results</h3>");
        String lastBenchmark = "";
        for (RunResult result : results) {
            BenchmarkParams benchParams = result.getParams();
            String benchmarkName = benchParams.getBenchmark().replace(SCENARIOS_PACKAGE, "");
            if (!benchmarkName.equals(lastBenchmark)) {
                String nodeCount = benchParams.getParam("nodeCount");
                String tagCardinality = benchParams.getParam("tagCardinality");
                out.println("<details>");
                out.print("<summary><b>" + benchmarkName + "</b> <i>[command='" + benchParams.getParam("command") + "'");
                if (nodeCount != null) {
                    out.print(", nodeCount=" + nodeCount);
                }
                if (tagCardinality != null) {
                    out.print(", tagCardinality=" + tagCardinality);
                }
                out.println("]</i>&#x1F50D;</summary>");
                out.println("<table width='100%'><thead><th>Metric</th><th>Score</th></thead>");
                out.println("<tbody>");
                for (String label : result.getSecondaryResults().keySet()) {
                    Result metric = result.getSecondaryResults().get(label);
                    out.println("<tr>");
                    out.print("<td>" + metric.getLabel() + "</td>");
                    out.println("<td>" + emit(metric.getScore()) + "</td>");
                    out.println("</tr>");
                }
                out.println("</tbody></table>");
                out.println("</details>");
                lastBenchmark = benchmarkName;
            }
        }
        endHtml();
    }

    private String emit(String v) {
        return v != null ? v : ""   ;
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
