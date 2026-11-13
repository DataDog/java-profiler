/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Checks a memcheck PR run against the budget file and writes a markdown report.
 *
 * <p>Usage: {@code java Evaluate.java <budget.txt> <report.md> <dir>...}, where each dir holds
 * a {@code runs/} directory of {@link CollectRun} records. Exit status: 0 within budget, 1 over
 * budget or a tripwire hit, 2 bad input (unreadable budget line, no records for a budgeted
 * scenario). The report is written in every case.
 *
 * <p>Budget lines are {@code scenario metric limit measured [key=value...]}, separated by
 * whitespace; {@code #} starts a comment. {@code scenario} may be {@code *}: every scenario that
 * has records. {@code metric} is one of
 * <ul>
 *   <li>a profiler counter such as {@code native_mem_max_bytes}: the mean over the profiled
 *       (nmt arm) runs; the profiler's own memory needs no no-profiler reference;
 *   <li>{@code nmt.<category>}: NMT committed memory, profiled mean minus no-profiler mean;
 *   <li>{@code proc.<field>}: a {@code /proc/<pid>/status} field such as {@code VmRSS}, likewise.
 * </ul>
 * {@code limit} is a size ({@code B}, {@code KiB}, {@code MiB}, {@code GiB}), {@code -} for a
 * report-only line, or {@code absent} for a tripwire: the NMT category must not appear in any
 * profiled run. {@code measured} is the value when the limit was last set (a size, or {@code -}),
 * shown so that growth below the limit stays visible.
 *
 * <p>Options: {@code per_method=<bytes> ref_methods=<n>} corrects a counter for sampling
 * coverage. In scenarios with more methods than the wall-clock sampler reaches (classesM), the
 * profiler's memory grows with the number of distinct methods seen in sampled stacks, which the
 * {@code line_number_tables} counter reports and which varies with the load on a shared runner.
 * The checked value is {@code value - per_method * (mean line_number_tables - ref_methods)}.
 */
public class Evaluate {

    private static final Pattern SIZE = Pattern.compile("(\\d+(?:\\.\\d+)?)(B|KiB|MiB|GiB)");
    private static final double KIB = 1024;
    private static final String PROFILED = "nmt";
    private static final String NO_PROFILER = "noprof";

    /** One budget line. {@code limit} is null for report-only and tripwire lines. */
    static final class Budget {
        final int line;
        final String scenario;
        final String metric;
        final Double limit;
        final boolean tripwire;
        final Double measured;
        final Map<String, String> options;

        Budget(int line, String scenario, String metric, Double limit, boolean tripwire,
               Double measured, Map<String, String> options) {
            this.line = line;
            this.scenario = scenario;
            this.metric = metric;
            this.limit = limit;
            this.tripwire = tripwire;
            this.measured = measured;
            this.options = options;
        }
    }

    /** One run record; NMT and /proc values are converted from KiB to bytes. */
    static final class Run {
        final String scenario;
        final String arm;
        final Map<String, Double> counters;
        final Map<String, Double> nmt;
        final Map<String, Double> proc;

        Run(String scenario, String arm, Map<String, Double> counters, Map<String, Double> nmt,
            Map<String, Double> proc) {
            this.scenario = scenario;
            this.arm = arm;
            this.counters = counters;
            this.nmt = nmt;
            this.proc = proc;
        }
    }

    /** The outcome of one budget line for one scenario. */
    static final class Row {
        final Budget budget;
        final String scenario;
        final Double value;
        final String status;
        final boolean failed;

        Row(Budget budget, String scenario, Double value, String status, boolean failed) {
            this.budget = budget;
            this.scenario = scenario;
            this.value = value;
            this.status = status;
            this.failed = failed;
        }
    }

    public static void main(String[] args) throws IOException {
        if (args.length < 3) {
            System.err.println("usage: java Evaluate.java <budget.txt> <report.md> <dir>...");
            System.exit(2);
        }
        List<String> errors = new ArrayList<>();
        List<Budget> budget = parseBudget(Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8), errors);
        List<Run> runs = new ArrayList<>();
        for (int i = 2; i < args.length; i++) {
            runs.addAll(readRuns(Paths.get(args[i], "runs")));
        }
        List<Row> rows = evaluate(budget, runs, errors);
        String report = report(rows, errors, Paths.get(args[2]));
        Files.write(Paths.get(args[1]), report.getBytes(StandardCharsets.UTF_8));
        System.out.print(report);
        System.exit(!errors.isEmpty() ? 2 : rows.stream().anyMatch(r -> r.failed) ? 1 : 0);
    }

    static List<Budget> parseBudget(List<String> lines, List<String> errors) {
        List<Budget> budget = new ArrayList<>();
        for (int n = 1; n <= lines.size(); n++) {
            String line = lines.get(n - 1).replaceFirst("#.*", "").trim();
            if (line.isEmpty()) {
                continue;
            }
            String[] f = line.split("\\s+");
            try {
                if (f.length < 4) {
                    throw new IllegalArgumentException("expected: scenario metric limit measured [key=value...]");
                }
                boolean tripwire = f[2].equals("absent");
                if (tripwire && !f[1].startsWith("nmt.")) {
                    throw new IllegalArgumentException("'absent' only applies to nmt.<category>");
                }
                Double limit = tripwire || f[2].equals("-") ? null : size(f[2]);
                Double measured = f[3].equals("-") ? null : size(f[3]);
                Map<String, String> options = new LinkedHashMap<>();
                for (int i = 4; i < f.length; i++) {
                    String[] kv = f[i].split("=", 2);
                    if (kv.length != 2) {
                        throw new IllegalArgumentException("option '" + f[i] + "' is not key=value");
                    }
                    options.put(kv[0], kv[1]);
                }
                if (options.containsKey("per_method") != options.containsKey("ref_methods")) {
                    throw new IllegalArgumentException("per_method and ref_methods go together");
                }
                budget.add(new Budget(n, f[0], f[1], limit, tripwire, measured, options));
            } catch (IllegalArgumentException e) {
                errors.add("budget line " + n + ": " + e.getMessage());
            }
        }
        return budget;
    }

    static double size(String s) {
        Matcher m = SIZE.matcher(s);
        if (!m.matches()) {
            throw new IllegalArgumentException("'" + s + "' is not a size like 256KiB or 1.5MiB");
        }
        int shift = Stream.of("B", "KiB", "MiB", "GiB").collect(Collectors.toList()).indexOf(m.group(2));
        return Double.parseDouble(m.group(1)) * Math.pow(KIB, shift);
    }

    static List<Run> readRuns(Path dir) throws IOException {
        List<Run> runs = new ArrayList<>();
        if (!Files.isDirectory(dir)) {
            return runs;
        }
        try (Stream<Path> files = Files.list(dir)) {
            for (Path p : files.filter(f -> f.toString().endsWith(".json")).sorted().collect(Collectors.toList())) {
                runs.add(toRun(new Json(new String(Files.readAllBytes(p), StandardCharsets.UTF_8)).object()));
            }
        }
        return runs;
    }

    @SuppressWarnings("unchecked")
    static Run toRun(Map<String, Object> r) {
        return new Run((String) r.get("scenario"), (String) r.get("arm"),
                numbers((Map<String, Object>) r.get("counters"), 1),
                numbers((Map<String, Object>) r.get("nmt_kb"), KIB),
                numbers((Map<String, Object>) r.get("proc_kb"), KIB));
    }

    private static Map<String, Double> numbers(Map<String, Object> m, double scale) {
        Map<String, Double> out = new LinkedHashMap<>();
        if (m != null) {
            m.forEach((k, v) -> out.put(k, ((Double) v) * scale));
        }
        return out;
    }

    static List<Row> evaluate(List<Budget> budget, List<Run> runs, List<String> errors) {
        TreeSet<String> scenarios = runs.stream().map(r -> r.scenario).collect(Collectors.toCollection(TreeSet::new));
        List<Row> rows = new ArrayList<>();
        for (Budget b : budget) {
            for (String scenario : b.scenario.equals("*") ? scenarios : new TreeSet<>(List.of(b.scenario))) {
                List<Run> profiled = select(runs, scenario, PROFILED);
                if (profiled.isEmpty()) {
                    errors.add("no profiled runs for scenario " + scenario + " (budget line " + b.line + ")");
                    continue;
                }
                rows.add(b.tripwire ? tripwire(b, scenario, profiled) : check(b, scenario, profiled,
                        select(runs, scenario, NO_PROFILER), errors));
            }
        }
        return rows;
    }

    private static List<Run> select(List<Run> runs, String scenario, String arm) {
        return runs.stream().filter(r -> r.scenario.equals(scenario) && r.arm.equals(arm)).collect(Collectors.toList());
    }

    private static Row tripwire(Budget b, String scenario, List<Run> profiled) {
        String category = b.metric.substring("nmt.".length());
        boolean present = profiled.stream().anyMatch(r -> r.nmt.containsKey(category));
        return new Row(b, scenario, null, present ? "PRESENT" : "absent", present);
    }

    private static Row check(Budget b, String scenario, List<Run> profiled, List<Run> noProfiler, List<String> errors) {
        Double value;
        if (b.metric.startsWith("nmt.") || b.metric.startsWith("proc.")) {
            if (noProfiler.isEmpty()) {
                errors.add("no no-profiler runs for scenario " + scenario + " (budget line " + b.line + ")");
                return new Row(b, scenario, null, "MISSING", true);
            }
            boolean nmt = b.metric.startsWith("nmt.");
            String key = b.metric.substring(b.metric.indexOf('.') + 1);
            value = mean(profiled, r -> (nmt ? r.nmt : r.proc).getOrDefault(key, 0.0))
                    - mean(noProfiler, r -> (nmt ? r.nmt : r.proc).getOrDefault(key, 0.0));
        } else {
            if (profiled.stream().noneMatch(r -> r.counters.containsKey(b.metric))) {
                errors.add("no counter " + b.metric + " in scenario " + scenario + " (budget line " + b.line + ")");
                return new Row(b, scenario, null, "MISSING", true);
            }
            value = mean(profiled, r -> r.counters.getOrDefault(b.metric, 0.0));
            if (b.options.containsKey("per_method")) {
                double methods = mean(profiled, r -> r.counters.getOrDefault("line_number_tables", 0.0));
                value -= Double.parseDouble(b.options.get("per_method"))
                        * (methods - Double.parseDouble(b.options.get("ref_methods")));
            }
        }
        if (b.limit == null) {
            return new Row(b, scenario, value, "report", false);
        }
        boolean over = value > b.limit;
        return new Row(b, scenario, value, over ? "OVER" : "ok", over);
    }

    private static double mean(List<Run> runs, java.util.function.ToDoubleFunction<Run> f) {
        return runs.stream().mapToDouble(f).average().orElse(Double.NaN);
    }

    static String report(List<Row> rows, List<String> errors, Path firstDir) throws IOException {
        boolean failed = rows.stream().anyMatch(r -> r.failed);
        StringBuilder sb = new StringBuilder("## Memory overhead check: ");
        sb.append(!errors.isEmpty() ? "⚠️ incomplete" : failed ? "❌ over budget" : "✅ within budget").append("\n\n");
        Path commit = firstDir.resolve("profiler-commit.txt");
        if (Files.exists(commit)) {
            String sha = Files.readAllLines(commit).get(0).trim();
            sb.append("Profiler `").append(sha, 0, Math.min(9, sha.length())).append("`");
        }
        String pipeline = System.getenv("CI_PIPELINE_URL");
        if (pipeline != null && !pipeline.isEmpty()) {
            sb.append(", [pipeline](").append(pipeline).append(")");
        }
        sb.append(". Budget: `utils/memcheck/budget.txt`. NMT and /proc values are profiled minus "
                + "no-profiler runs on the same runner.\n\n");
        for (String e : errors) {
            sb.append("- ⚠️ ").append(e).append('\n');
        }
        if (!errors.isEmpty()) {
            sb.append('\n');
        }
        sb.append("| scenario | metric | value | Δ since budget set | limit | headroom | |\n");
        sb.append("|---|---|---:|---:|---:|---:|---|\n");
        List<Row> gated = rows.stream().filter(r -> r.budget.limit != null || r.status.equals("MISSING"))
                .sorted(java.util.Comparator.comparing((Row r) -> r.scenario)).collect(Collectors.toList());
        for (Row r : gated) {
            Budget b = r.budget;
            sb.append("| ").append(r.scenario).append(" | `").append(b.metric).append('`')
                    .append(b.options.containsKey("per_method") ? " (coverage-corrected)" : "").append(" | ")
                    .append(r.value == null ? "" : fmt(r.value, false)).append(" | ")
                    .append(r.value == null || b.measured == null ? "" : fmt(r.value - b.measured, true)).append(" | ")
                    .append(b.limit == null ? "" : fmt(b.limit, false)).append(" | ")
                    .append(r.value == null || b.limit == null ? "" : fmt(b.limit - r.value, false)).append(" | ")
                    .append(r.failed ? "❌ " : "").append(r.status).append(" |\n");
        }
        for (String metric : rows.stream().filter(r -> r.budget.tripwire).map(r -> r.budget.metric)
                .collect(Collectors.toCollection(TreeSet::new))) {
            List<String> present = rows.stream().filter(r -> r.budget.tripwire && r.budget.metric.equals(metric) && r.failed)
                    .map(r -> r.scenario).sorted().collect(Collectors.toList());
            sb.append('\n').append(present.isEmpty() ? "✅ `" + metric + "` absent in every scenario."
                    : "❌ `" + metric + "` must be absent but appeared in: " + String.join(", ", present) + ".").append('\n');
        }
        List<Row> reported = rows.stream().filter(r -> r.status.equals("report")).collect(Collectors.toList());
        if (!reported.isEmpty()) {
            List<String> metrics = reported.stream().map(r -> r.budget.metric).distinct().collect(Collectors.toList());
            sb.append("\n<details><summary>Not budgeted (too noisy on shared runners)</summary>\n\n| scenario |");
            metrics.forEach(m -> sb.append(" `").append(m).append("` |"));
            sb.append("\n|---|").append("---:|".repeat(metrics.size())).append('\n');
            for (String scenario : reported.stream().map(r -> r.scenario).collect(Collectors.toCollection(TreeSet::new))) {
                sb.append("| ").append(scenario).append(" |");
                for (String m : metrics) {
                    sb.append(' ').append(reported.stream().filter(r -> r.scenario.equals(scenario) && r.budget.metric.equals(m))
                            .map(r -> fmt(r.value, false)).findFirst().orElse("")).append(" |");
                }
                sb.append('\n');
            }
            sb.append("\n</details>\n");
        }
        if (failed) {
            sb.append("\nA limit was exceeded. Either fix the regression, or raise the limit in "
                    + "`utils/memcheck/budget.txt` in this PR and explain why in the PR description.\n");
        }
        return sb.toString();
    }

    static String fmt(double bytes, boolean signed) {
        double a = Math.abs(bytes);
        String sign = signed ? (bytes < 0 ? "−" : "+") : (bytes < 0 ? "−" : "");
        return a >= KIB * KIB
                ? String.format(Locale.ROOT, "%s%.2f MiB", sign, a / (KIB * KIB))
                : String.format(Locale.ROOT, "%s%.0f KiB", sign, a / KIB);
    }

    /**
     * Parser for the flat JSON that {@link CollectRun} writes: objects, strings with {@code \\}
     * and {@code \"} escapes, and numbers.
     */
    static final class Json {
        private final String s;
        private int i;

        Json(String s) {
            this.s = s;
        }

        Map<String, Object> object() {
            Map<String, Object> m = new LinkedHashMap<>();
            expect('{');
            if (peek() == '}') {
                i++;
                return m;
            }
            while (true) {
                String key = string();
                expect(':');
                m.put(key, value());
                char c = next();
                if (c == '}') {
                    return m;
                }
                if (c != ',') {
                    throw error("expected ',' or '}'");
                }
            }
        }

        private Object value() {
            char c = peek();
            if (c == '{') {
                return object();
            }
            if (c == '"') {
                return string();
            }
            int start = i;
            while (i < s.length() && "+-0123456789.eE".indexOf(s.charAt(i)) >= 0) {
                i++;
            }
            if (start == i) {
                throw error("expected a value");
            }
            return Double.parseDouble(s.substring(start, i));
        }

        private String string() {
            expect('"');
            StringBuilder sb = new StringBuilder();
            for (char c = s.charAt(i++); c != '"'; c = s.charAt(i++)) {
                sb.append(c == '\\' ? s.charAt(i++) : c);
            }
            return sb.toString();
        }

        private void expect(char c) {
            if (next() != c) {
                throw error("expected '" + c + "'");
            }
        }

        private char next() {
            char c = peek();
            i++;
            return c;
        }

        private char peek() {
            while (i < s.length() && Character.isWhitespace(s.charAt(i))) {
                i++;
            }
            if (i >= s.length()) {
                throw error("unexpected end");
            }
            return s.charAt(i);
        }

        private IllegalArgumentException error(String msg) {
            return new IllegalArgumentException(msg + " at offset " + i);
        }
    }
}
