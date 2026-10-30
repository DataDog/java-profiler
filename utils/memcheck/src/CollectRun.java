/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

import jdk.jfr.consumer.RecordedEvent;
import jdk.jfr.consumer.RecordingFile;

import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Folds the artifacts of one memcheck run into a single JSON object:
 * <ul>
 *   <li>{@code counters}: the last value of every {@code datadog.ProfilerCounter}
 *       event in the final recording (the profiler's own counters, including
 *       the per-category {@code native_mem_*} gauges);</li>
 *   <li>{@code counters_middump}: the same, from the mid-run rotation;</li>
 *   <li>{@code nmt_kb}: committed KB per NMT category, from
 *       {@code jcmd VM.native_memory summary};</li>
 *   <li>{@code proc_kb}: {@code VmRSS}/{@code RssAnon}/{@code RssFile} from
 *       {@code /proc/<pid>/status}, taken at the same instant as NMT.</li>
 * </ul>
 * Missing inputs are skipped, so the same tool serves every arm.
 *
 * <p>Usage: {@code CollectRun key=value...} with keys {@code scenario, arm, rep,
 * jfr, middump, nmt, status, out}.
 */
public class CollectRun {
    private static final Pattern NMT_CATEGORY =
            Pattern.compile("^-\\s+(\\S.*?)\\s+\\(reserved=(\\d+)KB, committed=(\\d+)KB\\)");
    private static final Pattern NMT_TOTAL =
            Pattern.compile("^Total: reserved=(\\d+)KB, committed=(\\d+)KB");
    private static final Pattern PROC_FIELD = Pattern.compile("^(VmRSS|RssAnon|RssFile):\\s+(\\d+) kB");

    public static void main(String[] args) throws IOException {
        Map<String, String> opts = new LinkedHashMap<>();
        for (String a : args) {
            int eq = a.indexOf('=');
            opts.put(a.substring(0, eq), a.substring(eq + 1));
        }
        StringBuilder json = new StringBuilder("{");
        json.append("\"scenario\":").append(quote(opts.get("scenario")));
        json.append(",\"arm\":").append(quote(opts.get("arm")));
        json.append(",\"rep\":").append(Integer.parseInt(opts.get("rep")));
        json.append(",\"counters\":").append(object(counters(opts.get("jfr"))));
        json.append(",\"counters_middump\":").append(object(counters(opts.get("middump"))));
        json.append(",\"nmt_kb\":").append(object(nmt(opts.get("nmt"))));
        json.append(",\"proc_kb\":").append(object(proc(opts.get("status"))));
        json.append("}");
        try (PrintWriter w = new PrintWriter(Files.newBufferedWriter(Paths.get(opts.get("out"))))) {
            w.println(json);
        }
    }

    private static Map<String, Long> counters(String jfr) throws IOException {
        Map<String, Long> last = new LinkedHashMap<>();
        Path path = existing(jfr);
        if (path == null) {
            return last;
        }
        try (RecordingFile file = new RecordingFile(path)) {
            while (file.hasMoreEvents()) {
                RecordedEvent e = file.readEvent();
                if ("datadog.ProfilerCounter".equals(e.getEventType().getName())) {
                    last.put(e.getString("name"), ((Number) e.getValue("count")).longValue());
                }
            }
        }
        return last;
    }

    private static Map<String, Long> nmt(String summary) throws IOException {
        Map<String, Long> committed = new LinkedHashMap<>();
        for (String line : lines(summary)) {
            String trimmed = line.trim();
            Matcher total = NMT_TOTAL.matcher(trimmed);
            if (total.find()) {
                committed.put("total", Long.parseLong(total.group(2)));
                continue;
            }
            Matcher m = NMT_CATEGORY.matcher(line);
            if (m.find()) {
                committed.put(m.group(1).toLowerCase().replace(' ', '_'), Long.parseLong(m.group(3)));
            }
        }
        return committed;
    }

    private static Map<String, Long> proc(String status) throws IOException {
        Map<String, Long> kb = new LinkedHashMap<>();
        for (String line : lines(status)) {
            Matcher m = PROC_FIELD.matcher(line);
            if (m.find()) {
                kb.put(m.group(1), Long.parseLong(m.group(2)));
            }
        }
        return kb;
    }

    private static List<String> lines(String file) throws IOException {
        Path path = existing(file);
        return path == null ? List.of() : Files.readAllLines(path);
    }

    private static Path existing(String file) {
        if (file == null || file.isEmpty()) {
            return null;
        }
        Path path = Paths.get(file);
        return Files.isRegularFile(path) ? path : null;
    }

    private static String object(Map<String, Long> values) {
        StringBuilder sb = new StringBuilder("{");
        for (Map.Entry<String, Long> e : values.entrySet()) {
            if (sb.length() > 1) {
                sb.append(',');
            }
            sb.append(quote(e.getKey())).append(':').append(e.getValue());
        }
        return sb.append('}').toString();
    }

    private static String quote(String s) {
        return "\"" + s.replace("\\", "\\\\").replace("\"", "\\\"") + "\"";
    }
}
