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

import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Supplier;

import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.unit.UnitLookup;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.*;

/**
 * Central coordinator for all unwinding validation tests.
 * Provides unified execution, reporting, and validation across different test scenarios.
 */
public class UnwindingTestSuite {
    
    // Attribute definition for JFR analysis
    public static final IAttribute<String> THREAD_EXECUTION_MODE =
            attr("mode", "mode", "Execution Mode", PLAIN_TEXT);
    
    @FunctionalInterface
    public interface TestScenario {
        long execute() throws Exception;
    }
    
    private final List<TestResult> results = new ArrayList<>();
    private final Supplier<Iterable<IItemIterable>> samplesProvider;
    
    public UnwindingTestSuite(Supplier<Iterable<IItemIterable>> samplesProvider) {
        this.samplesProvider = samplesProvider;
    }
    
    /**
     * Execute a test scenario and collect results.
     */
    public void executeTest(String testName, String description, TestScenario scenario) {
        System.err.println("=== Executing: " + testName + " ===");
        
        long startTime = System.currentTimeMillis();
        long workCompleted = 0;
        
        try {
            workCompleted = scenario.execute();
            
            if (workCompleted <= 0) {
                throw new RuntimeException("Test scenario completed with no work performed");
            }
            
        } catch (Exception e) {
            System.err.println("ERROR: Test scenario failed: " + e.getMessage());
            // Create a failed result
            UnwindingMetrics.UnwindingResult emptyResult = createEmptyResult();
            TestResult failedResult = new TestResult(testName, description, emptyResult, 
                    TestResult.Status.NEEDS_WORK, "Test execution failed: " + e.getMessage(),
                    System.currentTimeMillis() - startTime);
            results.add(failedResult);
            return;
        }
        
        long executionTime = System.currentTimeMillis() - startTime;
        
        // Analyze results
        UnwindingMetrics.UnwindingResult metrics = analyzeTestResults();
        TestResult result = TestResult.create(testName, description, metrics, executionTime);
        results.add(result);
        
        System.err.println("Completed: " + testName + " (" + executionTime + "ms, " + 
                          metrics.totalSamples + " samples, " + 
                          String.format("%.2f%%", metrics.getErrorRate()) + " error rate)");

    }
    
    /**
     * Generate the unified dashboard report for all executed tests.
     */
    public String generateReport() {
        return UnwindingDashboard.generateReport(results);
    }
    
    /**
     * Generate a compact summary line suitable for CI.
     */
    public String generateCompactSummary() {
        return UnwindingDashboard.generateCompactSummary(results);
    }
    
    /**
     * Get all test results.
     */
    public List<TestResult> getResults() {
        return new ArrayList<>(results);
    }
    
    /**
     * Check if any tests require attention (moderate or needs work status).
     */
    public boolean hasIssues() {
        return results.stream().anyMatch(r -> 
                r.getStatus() == TestResult.Status.MODERATE || 
                r.getStatus() == TestResult.Status.NEEDS_WORK);
    }
    
    /**
     * Check if any tests have critical issues (needs work status).
     */
    public boolean hasCriticalIssues() {
        return results.stream().anyMatch(r -> r.getStatus() == TestResult.Status.NEEDS_WORK);
    }
    
    /**
     * Get the overall error rate across all tests.
     */
    public double getOverallErrorRate() {
        int totalSamples = results.stream().mapToInt(r -> r.getMetrics().totalSamples).sum();
        int totalErrors = results.stream().mapToInt(r -> r.getMetrics().errorSamples).sum();
        return totalSamples > 0 ? (double) totalErrors / totalSamples * 100 : 0.0;
    }
    
    /**
     * Clear all results (useful for test isolation).
     */
    public void reset() {
        results.clear();
    }
    
    private UnwindingMetrics.UnwindingResult analyzeTestResults() {
        try {
            Iterable<IItemIterable> cpuSamples = samplesProvider.get();
            IMemberAccessor<String, IItem> modeAccessor = null;
            
            // Get the mode accessor from the first sample
            for (IItemIterable samples : cpuSamples) {
                modeAccessor = THREAD_EXECUTION_MODE.getAccessor(samples.getType());
                break;
            }
            
            if (modeAccessor == null) {
                System.err.println("WARNING: Could not get mode accessor, creating empty result");
                return createEmptyResult();
            }
            
            return UnwindingMetrics.analyzeUnwindingData(cpuSamples, modeAccessor);
            
        } catch (Exception e) {
            System.err.println("ERROR: Failed to analyze test results: " + e.getMessage());
            return createEmptyResult();
        }
    }
    
    private UnwindingMetrics.UnwindingResult createEmptyResult() {
        return new UnwindingMetrics.UnwindingResult(0, 0, 0, 0, 0, 0, 0, 0, 0, 
                java.util.Collections.emptyMap(), java.util.Collections.emptyMap());
    }
    
    /**
     * Builder class for convenient test suite configuration.
     */
    public static class Builder {
        private final UnwindingTestSuite suite;
        
        public Builder(Supplier<Iterable<IItemIterable>> samplesProvider) {
            this.suite = new UnwindingTestSuite(samplesProvider);
        }
        
        public Builder addTest(String name, String description, TestScenario scenario) {
            return this;
        }
        
        public UnwindingTestSuite build() {
            return suite;
        }
    }
    
    /**
     * Common validation methods that can be used by test scenarios.
     */
    public static class ValidationUtils {
        
        public static void validateBasicRequirements(UnwindingMetrics.UnwindingResult result, String testName) {
            if (result.totalSamples == 0) {
                throw new RuntimeException(testName + ": No samples captured - test may not be exercising unwinding properly");
            }
            
            if (result.totalSamples < 10) {
                System.err.println("WARNING: " + testName + " captured only " + result.totalSamples + 
                                 " samples - may not be sufficient for reliable analysis");
            }
        }
        
        public static void validateNativeCoverage(UnwindingMetrics.UnwindingResult result, String testName, 
                                                double minimumNativeRate) {
            if (result.getNativeRate() < minimumNativeRate) {
                System.err.println("WARNING: " + testName + " has low native coverage: " + 
                                 String.format("%.1f%% (expected >= %.1f%%)", result.getNativeRate(), minimumNativeRate));
            }
        }
        
        public static void validateStubCoverage(UnwindingMetrics.UnwindingResult result, String testName) {
            if (result.stubSamples == 0) {
                System.err.println("INFO: " + testName + " captured no stub samples - may not be testing stub unwinding");
            }
        }
    }
}