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

/**
 * Standardized result object for unwinding validation tests.
 * Provides consistent structure for reporting test outcomes across different scenarios.
 */
public class TestResult {
    
    public enum Status {
        EXCELLENT("🟢", "Excellent unwinding quality"),
        GOOD("🟢", "Good unwinding quality"), 
        MODERATE("🟡", "Moderate unwinding quality - improvement recommended"),
        NEEDS_WORK("🔴", "Poor unwinding quality - requires attention");
        
        private final String indicator;
        private final String description;
        
        Status(String indicator, String description) {
            this.indicator = indicator;
            this.description = description;
        }
        
        public String getIndicator() { return indicator; }
        public String getDescription() { return description; }
    }
    
    private final String testName;
    private final String scenarioDescription;
    private final UnwindingMetrics.UnwindingResult metrics;
    private final Status status;
    private final String statusMessage;
    private final long executionTimeMs;
    
    public TestResult(String testName, String scenarioDescription, 
                     UnwindingMetrics.UnwindingResult metrics, 
                     Status status, String statusMessage, long executionTimeMs) {
        this.testName = testName;
        this.scenarioDescription = scenarioDescription;
        this.metrics = metrics;
        this.status = status;
        this.statusMessage = statusMessage;
        this.executionTimeMs = executionTimeMs;
    }
    
    public String getTestName() { return testName; }
    public String getScenarioDescription() { return scenarioDescription; }
    public UnwindingMetrics.UnwindingResult getMetrics() { return metrics; }
    public Status getStatus() { return status; }
    public String getStatusMessage() { return statusMessage; }
    public long getExecutionTimeMs() { return executionTimeMs; }
    
    /**
     * Determine test status based on error rate and other quality metrics.
     */
    public static Status determineStatus(UnwindingMetrics.UnwindingResult result) {
        double errorRate = result.getErrorRate();
        
        if (errorRate < 0.1) {
            return Status.EXCELLENT;
        } else if (errorRate < 1.0) {
            return Status.GOOD;
        } else if (errorRate < 5.0) {
            return Status.MODERATE;
        } else {
            return Status.NEEDS_WORK;
        }
    }
    
    /**
     * Generate appropriate status message based on metrics.
     */
    public static String generateStatusMessage(UnwindingMetrics.UnwindingResult result, Status status) {
        StringBuilder sb = new StringBuilder();
        
        switch (status) {
            case EXCELLENT:
                sb.append("Error rate < 0.1% - exceptional unwinding quality");
                break;
            case GOOD:
                sb.append("Error rate < 1.0% - good unwinding performance");
                break;
            case MODERATE:
                sb.append("Error rate ").append(String.format("%.2f%%", result.getErrorRate()))
                  .append(" - moderate, consider optimization");
                break;
            case NEEDS_WORK:
                sb.append("Error rate ").append(String.format("%.2f%%", result.getErrorRate()))
                  .append(" - requires investigation");
                break;
        }
        
        // Add specific issue highlights for problematic cases
        if (result.errorSamples > 0 && (status == Status.MODERATE || status == Status.NEEDS_WORK)) {
            if (!result.errorTypeBreakdown.isEmpty()) {
                sb.append(" (").append(result.errorTypeBreakdown.keySet().iterator().next()).append(")");
            }
        }
        
        return sb.toString();
    }
    
    /**
     * Create a TestResult from metrics with automatic status determination.
     */
    public static TestResult create(String testName, String scenarioDescription,
                                  UnwindingMetrics.UnwindingResult metrics, 
                                  long executionTimeMs) {
        Status status = determineStatus(metrics);
        String statusMessage = generateStatusMessage(metrics, status);
        return new TestResult(testName, scenarioDescription, metrics, status, statusMessage, executionTimeMs);
    }
    
    @Override
    public String toString() {
        return String.format("TestResult{name='%s', status=%s, errorRate=%.2f%%, samples=%d}", 
                           testName, status, metrics.getErrorRate(), metrics.totalSamples);
    }
}