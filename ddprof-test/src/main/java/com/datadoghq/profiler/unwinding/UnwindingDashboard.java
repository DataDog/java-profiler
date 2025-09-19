/*
 * Copyright 2025, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.unwinding;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * Unified dashboard for displaying unwinding test results in a consistent, 
 * easy-to-scan format. Replaces scattered console output with structured reporting.
 */
public class UnwindingDashboard {
    
    /**
     * Generate a comprehensive dashboard report for all test results.
     */
    public static String generateReport(List<TestResult> results) {
        if (results.isEmpty()) {
            return "=== No Test Results Available ===\n";
        }
        
        StringBuilder sb = new StringBuilder();
        
        // Header
        sb.append("=== Unwinding Quality Dashboard ===\n");
        generateSummaryTable(sb, results);
        
        // Overall assessment
        generateOverallAssessment(sb, results);
        
        // Detailed breakdowns for problematic tests
        generateDetailedBreakdowns(sb, results);
        
        // Performance summary
        generatePerformanceSummary(sb, results);
        
        return sb.toString();
    }
    
    private static void generateSummaryTable(StringBuilder sb, List<TestResult> results) {
        sb.append("\n");
        sb.append(String.format("%-35s | %6s | %8s | %10s | %12s | %s\n", 
                "Test Scenario", "Status", "Error%", "Samples", "Native%", "Execution"));
        sb.append(String.format("%-35s-|-%6s-|-%8s-|-%10s-|-%12s-|-%s\n", 
                "-----------------------------------", "------", "--------", "----------", "------------", "----------"));
        
        for (TestResult result : results) {
            UnwindingMetrics.UnwindingResult metrics = result.getMetrics();
            
            sb.append(String.format("%-35s | %4s   | %7.2f%% | %10d | %12.1f%% | %7dms\n",
                    truncateTestName(result.getTestName()),
                    result.getStatus().getIndicator(),
                    metrics.getErrorRate(),
                    metrics.totalSamples,
                    metrics.getNativeRate(),
                    result.getExecutionTimeMs()));
        }
    }
    
    private static void generateOverallAssessment(StringBuilder sb, List<TestResult> results) {
        sb.append("\n=== Overall Assessment ===\n");
        
        long excellentCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.EXCELLENT ? 1 : 0).sum();
        long goodCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.GOOD ? 1 : 0).sum();
        long moderateCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.MODERATE ? 1 : 0).sum();
        long needsWorkCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.NEEDS_WORK ? 1 : 0).sum();
        
        double avgErrorRate = results.stream()
                .mapToDouble(r -> r.getMetrics().getErrorRate())
                .average()
                .orElse(0.0);
        
        int totalSamples = results.stream()
                .mapToInt(r -> r.getMetrics().totalSamples)
                .sum();
        
        int totalErrors = results.stream()
                .mapToInt(r -> r.getMetrics().errorSamples)
                .sum();
        
        sb.append(String.format("Tests:        %d excellent, %d good, %d moderate, %d needs work\n", 
                excellentCount, goodCount, moderateCount, needsWorkCount));
        sb.append(String.format("Overall:      %.3f%% average error rate (%d errors / %d samples)\n", 
                avgErrorRate, totalErrors, totalSamples));
        
        // Overall quality assessment
        if (needsWorkCount > 0) {
            sb.append("🔴 ATTENTION: Some scenarios require investigation\n");
        } else if (moderateCount > 0) {
            sb.append("🟡 MODERATE: Good overall quality, some optimization opportunities\n");
        } else {
            sb.append("🟢 EXCELLENT: All unwinding scenarios performing well\n");
        }
    }
    
    private static void generateDetailedBreakdowns(StringBuilder sb, List<TestResult> results) {
        List<TestResult> problematicResults = results.stream()
                .filter(r -> r.getStatus() == TestResult.Status.MODERATE || 
                           r.getStatus() == TestResult.Status.NEEDS_WORK)
                .collect(Collectors.toList());
        
        if (problematicResults.isEmpty()) {
            return;
        }
        
        sb.append("\n=== Issue Details ===\n");
        
        for (TestResult result : problematicResults) {
            sb.append(String.format("\n%s %s:\n", result.getStatus().getIndicator(), result.getTestName()));
            sb.append(String.format("  %s\n", result.getStatusMessage()));
            
            UnwindingMetrics.UnwindingResult metrics = result.getMetrics();
            
            // Show error breakdown if available
            if (!metrics.errorTypeBreakdown.isEmpty()) {
                sb.append("  Error types: ");
                metrics.errorTypeBreakdown.forEach((type, count) -> 
                    sb.append(String.format("%s:%d ", type, count)));
                sb.append("\n");
            }
            
            // Show stub coverage if relevant
            if (metrics.stubSamples > 0 && !metrics.stubTypeBreakdown.isEmpty()) {
                sb.append("  Stub types: ");
                metrics.stubTypeBreakdown.forEach((type, count) -> 
                    sb.append(String.format("%s:%d ", type, count)));
                sb.append("\n");
            }
            
            // Key metrics
            if (metrics.nativeSamples > 0) {
                sb.append(String.format("  Native coverage: %d/%d samples (%.1f%%)\n", 
                        metrics.nativeSamples, metrics.totalSamples, metrics.getNativeRate()));
            }
        }
    }
    
    private static void generatePerformanceSummary(StringBuilder sb, List<TestResult> results) {
        sb.append("\n=== Test Execution Summary ===\n");
        
        long totalExecutionTime = results.stream().mapToLong(TestResult::getExecutionTimeMs).sum();
        long maxExecutionTime = results.stream().mapToLong(TestResult::getExecutionTimeMs).max().orElse(0);
        String slowestTest = results.stream()
                .filter(r -> r.getExecutionTimeMs() == maxExecutionTime)
                .map(TestResult::getTestName)
                .findFirst()
                .orElse("unknown");
        
        sb.append(String.format("Total execution: %d seconds\n", totalExecutionTime / 1000));
        sb.append(String.format("Slowest test: %s (%d seconds)\n", truncateTestName(slowestTest), maxExecutionTime / 1000));
        
        // Test coverage summary
        int totalSamples = results.stream().mapToInt(r -> r.getMetrics().totalSamples).sum();
        int totalNativeSamples = results.stream().mapToInt(r -> r.getMetrics().nativeSamples).sum();
        int totalStubSamples = results.stream().mapToInt(r -> r.getMetrics().stubSamples).sum();
        
        sb.append(String.format("Sample coverage: %d total, %d native (%.1f%%), %d stub (%.1f%%)\n",
                totalSamples, 
                totalNativeSamples, totalSamples > 0 ? (double) totalNativeSamples / totalSamples * 100 : 0.0,
                totalStubSamples, totalSamples > 0 ? (double) totalStubSamples / totalSamples * 100 : 0.0));
    }
    
    private static String truncateTestName(String testName) {
        if (testName.length() <= 35) {
            return testName;
        }
        return testName.substring(0, 32) + "...";
    }
    
    /**
     * Generate a compact single-line summary suitable for CI logs.
     */
    public static String generateCompactSummary(List<TestResult> results) {
        if (results.isEmpty()) {
            return "UNWINDING: No tests executed";
        }
        
        long problemCount = results.stream()
                .mapToLong(r -> (r.getStatus() == TestResult.Status.MODERATE || 
                                r.getStatus() == TestResult.Status.NEEDS_WORK) ? 1 : 0)
                .sum();
        
        double avgErrorRate = results.stream()
                .mapToDouble(r -> r.getMetrics().getErrorRate())
                .average()
                .orElse(0.0);
        
        int totalSamples = results.stream()
                .mapToInt(r -> r.getMetrics().totalSamples)
                .sum();
        
        String status = problemCount == 0 ? "PASS" : "ISSUES";
        
        return String.format("UNWINDING: %s - %d tests, %.3f%% avg error rate, %d samples, %d issues", 
                status, results.size(), avgErrorRate, totalSamples, problemCount);
    }
    
    /**
     * Generate a GitHub Actions Job Summary compatible markdown report.
     */
    public static String generateMarkdownReport(List<TestResult> results) {
        if (results.isEmpty()) {
            return "## 🔍 Unwinding Quality Report\n\n❌ No test results available\n";
        }
        
        StringBuilder md = new StringBuilder();
        
        // Header with timestamp and platform info
        md.append("## 🔍 Unwinding Quality Report\n\n");
        md.append("**Generated**: ").append(java.time.Instant.now()).append("  \n");
        md.append("**Platform**: ").append(System.getProperty("os.name"))
          .append(" ").append(System.getProperty("os.arch")).append("  \n");
        md.append("**Java**: ").append(System.getProperty("java.version")).append("\n\n");
        
        // Overall status summary
        generateMarkdownSummary(md, results);
        
        // Detailed results table
        generateMarkdownResultsTable(md, results);
        
        // Issue details if any
        generateMarkdownIssueDetails(md, results);
        
        // Performance footer
        generateMarkdownPerformanceFooter(md, results);
        
        return md.toString();
    }
    
    private static void generateMarkdownSummary(StringBuilder md, List<TestResult> results) {
        long excellentCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.EXCELLENT ? 1 : 0).sum();
        long goodCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.GOOD ? 1 : 0).sum();
        long moderateCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.MODERATE ? 1 : 0).sum();
        long needsWorkCount = results.stream().mapToLong(r -> r.getStatus() == TestResult.Status.NEEDS_WORK ? 1 : 0).sum();
        
        double avgErrorRate = results.stream()
                .mapToDouble(r -> r.getMetrics().getErrorRate())
                .average()
                .orElse(0.0);
        
        int totalSamples = results.stream()
                .mapToInt(r -> r.getMetrics().totalSamples)
                .sum();
        
        int totalErrors = results.stream()
                .mapToInt(r -> r.getMetrics().errorSamples)
                .sum();
        
        // Summary section with badges
        md.append("### 📊 Summary\n\n");
        
        if (needsWorkCount > 0) {
            md.append("🔴 **ATTENTION**: Some scenarios require investigation  \n");
        } else if (moderateCount > 0) {
            md.append("🟡 **MODERATE**: Good overall quality, optimization opportunities available  \n");
        } else {
            md.append("🟢 **EXCELLENT**: All unwinding scenarios performing well  \n");
        }
        
        md.append("**Results**: ");
        if (excellentCount > 0) md.append("🟢 ").append(excellentCount).append(" excellent ");
        if (goodCount > 0) md.append("🟢 ").append(goodCount).append(" good ");
        if (moderateCount > 0) md.append("🟡 ").append(moderateCount).append(" moderate ");
        if (needsWorkCount > 0) md.append("🔴 ").append(needsWorkCount).append(" needs work ");
        md.append("  \n");
        
        md.append("**Error Rate**: ").append(String.format("%.3f%%", avgErrorRate))
          .append(" (").append(totalErrors).append(" errors / ").append(totalSamples).append(" samples)  \n\n");
    }
    
    private static void generateMarkdownResultsTable(StringBuilder md, List<TestResult> results) {
        md.append("### 🎯 Scenario Results\n\n");
        
        md.append("| Scenario | Status | Error Rate | Samples | Native % | Duration |\n");
        md.append("|----------|--------|------------|---------|----------|---------|\n");
        
        for (TestResult result : results) {
            UnwindingMetrics.UnwindingResult metrics = result.getMetrics();
            
            md.append("| ").append(truncateForTable(result.getTestName(), 25))
              .append(" | ").append(result.getStatus().getIndicator())
              .append(" | ").append(String.format("%.2f%%", metrics.getErrorRate()))
              .append(" | ").append(String.format("%,d", metrics.totalSamples))
              .append(" | ").append(String.format("%.1f%%", metrics.getNativeRate()))
              .append(" | ").append(String.format("%.1fs", result.getExecutionTimeMs() / 1000.0))
              .append(" |\n");
        }
        
        md.append("\n");
    }
    
    private static void generateMarkdownIssueDetails(StringBuilder md, List<TestResult> results) {
        List<TestResult> problematicResults = results.stream()
                .filter(r -> r.getStatus() == TestResult.Status.MODERATE || 
                           r.getStatus() == TestResult.Status.NEEDS_WORK)
                .collect(Collectors.toList());
        
        if (problematicResults.isEmpty()) {
            return;
        }
        
        md.append("### ⚠️ Issues Requiring Attention\n\n");
        
        for (TestResult result : problematicResults) {
            UnwindingMetrics.UnwindingResult metrics = result.getMetrics();
            
            md.append("#### ").append(result.getStatus().getIndicator()).append(" ")
              .append(result.getTestName()).append("\n\n");
            md.append("**Issue**: ").append(result.getStatusMessage()).append("  \n");
            
            if (!metrics.errorTypeBreakdown.isEmpty()) {
                md.append("**Error types**: ");
                metrics.errorTypeBreakdown.forEach((type, count) -> 
                    md.append("`").append(truncateForTable(type, 30)).append("`:")
                      .append(count).append(" "));
                md.append("  \n");
            }
            
            if (metrics.nativeSamples > 0) {
                md.append("**Native coverage**: ").append(metrics.nativeSamples)
                  .append("/").append(metrics.totalSamples)
                  .append(" (").append(String.format("%.1f%%", metrics.getNativeRate())).append(")  \n");
            }
            
            md.append("\n");
        }
    }
    
    private static void generateMarkdownPerformanceFooter(StringBuilder md, List<TestResult> results) {
        long totalExecutionTime = results.stream().mapToLong(TestResult::getExecutionTimeMs).sum();
        long maxExecutionTime = results.stream().mapToLong(TestResult::getExecutionTimeMs).max().orElse(0);
        String slowestTest = results.stream()
                .filter(r -> r.getExecutionTimeMs() == maxExecutionTime)
                .map(TestResult::getTestName)
                .findFirst()
                .orElse("unknown");
        
        int totalSamples = results.stream().mapToInt(r -> r.getMetrics().totalSamples).sum();
        int totalNativeSamples = results.stream().mapToInt(r -> r.getMetrics().nativeSamples).sum();
        int totalStubSamples = results.stream().mapToInt(r -> r.getMetrics().stubSamples).sum();
        
        md.append("---\n\n");
        md.append("**⚡ Performance**: ").append(String.format("%.1fs", totalExecutionTime / 1000.0))
          .append(" total execution time  \n");
        md.append("**🐌 Slowest test**: ").append(truncateForTable(slowestTest, 20))
          .append(" (").append(String.format("%.1fs", maxExecutionTime / 1000.0)).append(")  \n");
        md.append("**📈 Coverage**: ").append(String.format("%,d", totalSamples)).append(" total samples, ")
          .append(String.format("%,d", totalNativeSamples)).append(" native (")
          .append(String.format("%.1f%%", totalSamples > 0 ? (double) totalNativeSamples / totalSamples * 100 : 0.0))
          .append("), ").append(String.format("%,d", totalStubSamples)).append(" stub (")
          .append(String.format("%.1f%%", totalSamples > 0 ? (double) totalStubSamples / totalSamples * 100 : 0.0))
          .append(")  \n");
    }
    
    private static String truncateForTable(String text, int maxLength) {
        if (text.length() <= maxLength) {
            return text;
        }
        return text.substring(0, maxLength - 3) + "...";
    }
}