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
 * budget or a tripwire hit, 2 bad input (unreadable budget line or record, no records or no
 * value for a budgeted metric). The report is written unless the budget file cannot be read.
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
 *
 * <p>Calibration: {@code java Evaluate.java --calibrate <budget.txt> <new-budget.txt> <job-dir>...}
 * recomputes every gated line of a single scenario from a calibration run, one dir per CI job,
 * and writes the budget with those lines replaced; comments, {@code *} lines and report-only
 * lines are kept as they are. See {@link #calibrate(Budget, List)} for the rule. Exit status 2
 * and no file written if a line cannot be recomputed.
 */
public class Evaluate {

    private static final Pattern SIZE = Pattern.compile("(\\d+(?:\\.\\d+)?)(B|KiB|MiB|GiB)");
    private static final double KIB = 1024;
    private static final double MIB = KIB * KIB;
    /** Smallest margin between the measured value and the limit. */
    private static final double FLOOR = 256 * KIB;
    /** Limits are rounded up to a multiple of this. */
    private static final double STEP = 0.05 * MIB;
    private static final String PROFILED = "nmt";
    private static final String NO_PROFILER = "noprof";
    /** The arm whose records carry the counters but no NMT; calibration pools it for the coverage slope. */
    private static final String COUNTERS_ONLY = "counters";

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

    /** Values derived for one budget line from a calibration run. {@code perMethod} is null without coverage correction. */
    static final class Calibration {
        final double measured;
        final double limit;
        final double sd;
        final double spread;
        final Long perMethod;
        final Long refMethods;

        Calibration(double measured, double limit, double sd, double spread, Long perMethod, Long refMethods) {
            this.measured = measured;
            this.limit = limit;
            this.sd = sd;
            this.spread = spread;
            this.perMethod = perMethod;
            this.refMethods = refMethods;
        }
    }

    public static void main(String[] args) {
        try {
            System.exit(args.length > 0 && args[0].equals("--calibrate") ? calibrateMain(args) : evaluateMain(args));
        } catch (IOException e) {
            // Exit 1 means over budget; unreadable input must not look like that.
            System.err.println("error: " + e.getMessage());
            System.exit(2);
        }
    }

    static int evaluateMain(String[] args) throws IOException {
        if (args.length < 3) {
            System.err.println("usage: java Evaluate.java <budget.txt> <report.md> <dir>...");
            return 2;
        }
        List<String> errors = new ArrayList<>();
        List<Budget> budget = parseBudget(Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8), errors);
        List<Run> runs = new ArrayList<>();
        for (int i = 2; i < args.length; i++) {
            try {
                runs.addAll(readRuns(Paths.get(args[i], "runs")));
            } catch (IOException e) {
                errors.add(e.getMessage());
            }
        }
        List<Row> rows = evaluate(budget, runs, errors);
        String report = report(rows, errors, Paths.get(args[2]));
        Files.write(Paths.get(args[1]), report.getBytes(StandardCharsets.UTF_8));
        System.out.print(report);
        return !errors.isEmpty() ? 2 : rows.stream().anyMatch(r -> r.failed) ? 1 : 0;
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
                try {
                    runs.add(toRun(new Json(new String(Files.readAllBytes(p), StandardCharsets.UTF_8)).object()));
                } catch (RuntimeException e) {
                    throw new IOException(p + " is not a run record: " + e, e);
                }
            }
        }
        return runs;
    }

    @SuppressWarnings("unchecked")
    static Run toRun(Map<String, Object> r) {
        if (!(r.get("scenario") instanceof String) || !(r.get("arm") instanceof String)) {
            throw new IllegalArgumentException("no scenario or arm");
        }
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
            // A report-only line cannot fail the check, so a category missing from one arm shows as 0.
            long lacking = b.limit == null ? 0 : lacking(Stream.concat(profiled.stream(), noProfiler.stream()), b.metric);
            if (lacking > 0) {
                errors.add(lacking + " run(s) of scenario " + scenario + " lack " + b.metric + " (budget line " + b.line + ")");
                return new Row(b, scenario, null, "MISSING", true);
            }
            value = mean(profiled, delta(b.metric)) - mean(noProfiler, delta(b.metric));
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

    /** The values an {@code nmt.} or {@code proc.} metric reads from in one run. */
    private static java.util.function.Function<Run, Map<String, Double>> section(String metric) {
        return metric.startsWith("nmt.") ? r -> r.nmt : r -> r.proc;
    }

    private static String key(String metric) {
        return metric.substring(metric.indexOf('.') + 1);
    }

    /** The value of an {@code nmt.} or {@code proc.} metric in one run, 0 if the run lacks it. */
    private static java.util.function.ToDoubleFunction<Run> delta(String metric) {
        java.util.function.Function<Run, Map<String, Double>> section = section(metric);
        String key = key(metric);
        return r -> section.apply(r).getOrDefault(key, 0.0);
    }

    /** Runs without the metric. A gated line must have none: counting a missing value as 0 would pass the gate. */
    private static long lacking(Stream<Run> runs, String metric) {
        java.util.function.Function<Run, Map<String, Double>> section = section(metric);
        String key = key(metric);
        return runs.filter(r -> !section.apply(r).containsKey(key)).count();
    }

    private static double mean(List<Run> runs, java.util.function.ToDoubleFunction<Run> f) {
        return runs.stream().mapToDouble(f).average().orElse(Double.NaN);
    }

    private static double sd(List<Run> runs, java.util.function.ToDoubleFunction<Run> f) {
        double m = mean(runs, f);
        double ss = runs.stream().mapToDouble(r -> Math.pow(f.applyAsDouble(r) - m, 2)).sum();
        return Math.sqrt(ss / (runs.size() - 1));
    }

    static int calibrateMain(String[] args) throws IOException {
        if (args.length < 4) {
            System.err.println("usage: java Evaluate.java --calibrate <budget.txt> <new-budget.txt> <job-dir>...");
            return 2;
        }
        List<String> lines = Files.readAllLines(Paths.get(args[1]), StandardCharsets.UTF_8);
        List<String> errors = new ArrayList<>();
        List<Budget> budget = parseBudget(lines, errors);
        List<List<Run>> jobs = new ArrayList<>();
        for (int i = 3; i < args.length; i++) {
            jobs.add(readRuns(Paths.get(args[i], "runs")));
        }
        List<String> out = new ArrayList<>(lines);
        for (Budget b : budget) {
            if (b.limit == null || b.scenario.equals("*")) {
                continue;
            }
            try {
                Calibration c = calibrate(b, jobs);
                out.set(b.line - 1, budgetLine(b, c));
                System.out.printf(Locale.ROOT, "line %d %s %s: limit %s -> %s, measured %s -> %s%n", b.line, b.scenario,
                        b.metric, fmt(b.limit, false), fmt(c.limit, false),
                        b.measured == null ? "-" : fmt(b.measured, false), fmt(c.measured, false));
            } catch (IllegalArgumentException e) {
                errors.add("budget line " + b.line + ": " + e.getMessage());
            }
        }
        if (!errors.isEmpty()) {
            errors.forEach(e -> System.err.println("error: " + e));
            return 2;
        }
        Files.write(Paths.get(args[2]), (String.join("\n", out) + "\n").getBytes(StandardCharsets.UTF_8));
        return 0;
    }

    /**
     * Derives one budget line from a calibration run: {@code limit = measured + max(FLOOR, 4 * sd)},
     * rounded up to a multiple of {@code STEP}, where {@code sd} is the largest within-job standard
     * deviation of the profiled runs, so the limit covers the noise of the noisiest pod. Counters
     * take {@code measured} as the mean of all profiled runs; NMT and /proc lines as the mean over
     * jobs of each job's profiled minus no-profiler mean, as {@link #check} computes it. With
     * coverage correction, the slope comes from a least-squares fit over the profiled and the
     * counters-only runs together (the per-job fits scatter too much), and {@code ref_methods} is
     * their mean method count, rounded to 100.
     */
    static Calibration calibrate(Budget b, List<List<Run>> jobs) {
        List<List<Run>> profiled = new ArrayList<>();
        for (List<Run> job : jobs) {
            List<Run> p = select(job, b.scenario, PROFILED);
            if (p.size() < 2) {
                throw new IllegalArgumentException("every job needs at least 2 profiled runs of " + b.scenario);
            }
            profiled.add(p);
        }
        java.util.function.ToDoubleFunction<Run> value;
        boolean delta = b.metric.startsWith("nmt.") || b.metric.startsWith("proc.");
        Long perMethod = null;
        Long refMethods = null;
        if (delta) {
            long lacking = lacking(jobs.stream().flatMap(List::stream).filter(r -> r.scenario.equals(b.scenario)
                    && (r.arm.equals(PROFILED) || r.arm.equals(NO_PROFILER))), b.metric);
            if (lacking > 0) {
                throw new IllegalArgumentException(lacking + " run(s) of " + b.scenario + " lack " + b.metric);
            }
            value = delta(b.metric);
        } else {
            if (profiled.stream().flatMap(List::stream).anyMatch(r -> !r.counters.containsKey(b.metric))) {
                throw new IllegalArgumentException("a profiled run of " + b.scenario + " lacks counter " + b.metric);
            }
            java.util.function.ToDoubleFunction<Run> raw = r -> r.counters.get(b.metric);
            value = raw;
            if (b.options.containsKey("per_method")) {
                java.util.function.ToDoubleFunction<Run> methods = r -> r.counters.getOrDefault("line_number_tables", 0.0);
                List<Run> both = jobs.stream().flatMap(List::stream)
                        .filter(r -> r.scenario.equals(b.scenario) && (r.arm.equals(PROFILED) || r.arm.equals(COUNTERS_ONLY)))
                        .collect(Collectors.toList());
                double mx = mean(both, methods);
                double my = mean(both, raw);
                double sxx = both.stream().mapToDouble(r -> Math.pow(methods.applyAsDouble(r) - mx, 2)).sum();
                if (sxx == 0) {
                    throw new IllegalArgumentException("line_number_tables does not vary in " + b.scenario + "; no coverage slope");
                }
                double sxy = both.stream().mapToDouble(r -> (methods.applyAsDouble(r) - mx) * (raw.applyAsDouble(r) - my)).sum();
                long slope = Math.round(sxy / sxx);
                long ref = Math.round(mx / 100) * 100;
                perMethod = slope;
                refMethods = ref;
                value = r -> raw.applyAsDouble(r) - slope * (methods.applyAsDouble(r) - ref);
            }
        }
        double sd = 0;
        List<Double> jobMeans = new ArrayList<>();
        for (int j = 0; j < jobs.size(); j++) {
            List<Run> p = profiled.get(j);
            sd = Math.max(sd, sd(p, value));
            double m = mean(p, value);
            if (delta) {
                List<Run> noProfiler = select(jobs.get(j), b.scenario, NO_PROFILER);
                if (noProfiler.isEmpty()) {
                    throw new IllegalArgumentException("a job has no no-profiler runs of " + b.scenario);
                }
                m -= mean(noProfiler, value);
            }
            jobMeans.add(m);
        }
        double measured = delta ? jobMeans.stream().mapToDouble(Double::doubleValue).average().orElse(Double.NaN)
                : mean(profiled.stream().flatMap(List::stream).collect(Collectors.toList()), value);
        if (measured < 0) {
            throw new IllegalArgumentException("measured " + fmt(measured, true) + " is negative; sizes cannot be negative");
        }
        double spread = jobMeans.stream().mapToDouble(Double::doubleValue).max().getAsDouble()
                - jobMeans.stream().mapToDouble(Double::doubleValue).min().getAsDouble();
        double limit = Math.ceil((measured + Math.max(FLOOR, 4 * sd)) / STEP) * STEP;
        return new Calibration(measured, limit, sd, spread, perMethod, refMethods);
    }

    static String budgetLine(Budget b, Calibration c) {
        String options = c.perMethod == null ? "" : "  per_method=" + c.perMethod + " ref_methods=" + c.refMethods;
        return String.format(Locale.ROOT, "%-9s %-22s %.2fMiB  %.2fMiB%s   # SD %d KiB, per-job spread %d KiB",
                b.scenario, b.metric, c.limit / MIB, c.measured / MIB, options, Math.round(c.sd / KIB),
                Math.round(c.spread / KIB));
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
