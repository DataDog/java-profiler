package com.datadoghq.profiler.unwinding;

import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

/**
 * Utility class for collecting and analyzing stub unwinding metrics from JFR data.
 * Provides standardized measurement and comparison of stackwalking performance
 * across different tests and configurations.
 */
public class UnwindingMetrics {
    
    public static class UnwindingResult {
        public final int totalSamples;
        public final int nativeSamples;
        public final int errorSamples;
        public final int stubSamples;
        public final int pltSamples;
        public final int jniSamples;
        public final int reflectionSamples;
        public final int jitSamples;
        public final int methodHandleSamples;
        public final Map<String, Integer> errorTypeBreakdown;
        public final Map<String, Integer> stubTypeBreakdown;
        
        public UnwindingResult(int totalSamples, int nativeSamples, int errorSamples, 
                              int stubSamples, int pltSamples, int jniSamples, 
                              int reflectionSamples, int jitSamples, int methodHandleSamples,
                              Map<String, Integer> errorTypeBreakdown,
                              Map<String, Integer> stubTypeBreakdown) {
            this.totalSamples = totalSamples;
            this.nativeSamples = nativeSamples;
            this.errorSamples = errorSamples;
            this.stubSamples = stubSamples;
            this.pltSamples = pltSamples;
            this.jniSamples = jniSamples;
            this.reflectionSamples = reflectionSamples;
            this.jitSamples = jitSamples;
            this.methodHandleSamples = methodHandleSamples;
            this.errorTypeBreakdown = errorTypeBreakdown;
            this.stubTypeBreakdown = stubTypeBreakdown;
        }
        
        public double getErrorRate() {
            return totalSamples > 0 ? (double) errorSamples / totalSamples * 100 : 0.0;
        }
        
        public double getNativeRate() {
            return totalSamples > 0 ? (double) nativeSamples / totalSamples * 100 : 0.0;
        }
        
        public double getStubRate() {
            return totalSamples > 0 ? (double) stubSamples / totalSamples * 100 : 0.0;
        }
        
        public double getPLTRate() {
            return totalSamples > 0 ? (double) pltSamples / totalSamples * 100 : 0.0;
        }
        
        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("UnwindingResult{\n");
            sb.append("  totalSamples=").append(totalSamples).append("\n");
            sb.append("  errorSamples=").append(errorSamples).append(" (").append(String.format("%.2f%%", getErrorRate())).append(")\n");
            sb.append("  nativeSamples=").append(nativeSamples).append(" (").append(String.format("%.2f%%", getNativeRate())).append(")\n");
            sb.append("  stubSamples=").append(stubSamples).append(" (").append(String.format("%.2f%%", getStubRate())).append(")\n");
            sb.append("  pltSamples=").append(pltSamples).append(" (").append(String.format("%.2f%%", getPLTRate())).append(")\n");
            sb.append("  jniSamples=").append(jniSamples).append("\n");
            sb.append("  reflectionSamples=").append(reflectionSamples).append("\n");
            sb.append("  jitSamples=").append(jitSamples).append("\n");
            sb.append("  methodHandleSamples=").append(methodHandleSamples).append("\n");
            
            if (!errorTypeBreakdown.isEmpty()) {
                sb.append("  errorTypes=").append(errorTypeBreakdown).append("\n");
            }
            if (!stubTypeBreakdown.isEmpty()) {
                sb.append("  stubTypes=").append(stubTypeBreakdown).append("\n");
            }
            sb.append("}");
            return sb.toString();
        }
    }
    
    /**
     * Analyze JFR execution samples and extract comprehensive unwinding metrics.
     */
    public static UnwindingResult analyzeUnwindingData(Iterable<IItemIterable> cpuSamples, 
                                                      IMemberAccessor<String, IItem> modeAccessor) {
        AtomicInteger totalSamples = new AtomicInteger(0);
        AtomicInteger nativeSamples = new AtomicInteger(0);
        AtomicInteger errorSamples = new AtomicInteger(0);
        AtomicInteger stubSamples = new AtomicInteger(0);
        AtomicInteger pltSamples = new AtomicInteger(0);
        AtomicInteger jniSamples = new AtomicInteger(0);
        AtomicInteger reflectionSamples = new AtomicInteger(0);
        AtomicInteger jitSamples = new AtomicInteger(0);
        AtomicInteger methodHandleSamples = new AtomicInteger(0);
        
        Map<String, AtomicInteger> errorTypes = new HashMap<>();
        Map<String, AtomicInteger> stubTypes = new HashMap<>();

        for (IItemIterable samples : cpuSamples) {
            IMemberAccessor<String, IItem> stacktraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());

            for (IItem item : samples) {
                totalSamples.incrementAndGet();
                String stackTrace = stacktraceAccessor.getMember(item);
                String mode = modeAccessor.getMember(item);

                if ("NATIVE".equals(mode)) {
                    nativeSamples.incrementAndGet();
                }

                if (containsJNIMethod(stackTrace)) {
                    jniSamples.incrementAndGet();
                }
                
                if (containsStubMethod(stackTrace)) {
                    stubSamples.incrementAndGet();
                    categorizeStubType(stackTrace, stubTypes);
                }
                
                if (containsPLTReference(stackTrace)) {
                    pltSamples.incrementAndGet();
                }
                
                if (containsReflectionMethod(stackTrace)) {
                    reflectionSamples.incrementAndGet();
                }
                
                if (containsJITReference(stackTrace)) {
                    jitSamples.incrementAndGet();
                }
                
                if (containsMethodHandleReference(stackTrace)) {
                    methodHandleSamples.incrementAndGet();
                }

                if (containsError(stackTrace)) {
                    errorSamples.incrementAndGet();
                    categorizeErrorType(stackTrace, errorTypes);
                }
            }
        }
        
        // Convert AtomicInteger maps to regular Integer maps
        Map<String, Integer> errorTypeBreakdown = new HashMap<>();
        errorTypes.forEach((k, v) -> errorTypeBreakdown.put(k, v.get()));
        
        Map<String, Integer> stubTypeBreakdown = new HashMap<>();
        stubTypes.forEach((k, v) -> stubTypeBreakdown.put(k, v.get()));

        return new UnwindingResult(
            totalSamples.get(), nativeSamples.get(), errorSamples.get(),
            stubSamples.get(), pltSamples.get(), jniSamples.get(),
            reflectionSamples.get(), jitSamples.get(), methodHandleSamples.get(),
            errorTypeBreakdown, stubTypeBreakdown
        );
    }
    
    private static void categorizeErrorType(String stackTrace, Map<String, AtomicInteger> errorTypes) {
        Set<String> observedErrors = Arrays.stream(stackTrace.split(System.lineSeparator())).filter(UnwindingMetrics::containsError).collect(Collectors.toSet());
        observedErrors.forEach(f -> errorTypes.computeIfAbsent(f, k -> new AtomicInteger()).incrementAndGet());
    }
    
    private static void categorizeStubType(String stackTrace, Map<String, AtomicInteger> stubTypes) {
        Set<String> observedStubs = Arrays.stream(stackTrace.split(System.lineSeparator())).filter(UnwindingMetrics::containsStubMethod).collect(Collectors.toSet());
        observedStubs.forEach(f -> stubTypes.computeIfAbsent(f, k -> new AtomicInteger()).incrementAndGet());
    }
    
    // Pattern detection methods (reused from individual tests)
    private static boolean containsJNIMethod(String stackTrace) {
        return stackTrace.contains("DirectByteBuffer") || 
               stackTrace.contains("Unsafe") ||
               stackTrace.contains("System.arraycopy") ||
               stackTrace.contains("ByteBuffer.get") ||
               stackTrace.contains("ByteBuffer.put") ||
               stackTrace.contains("ByteBuffer.allocateDirect");
    }

    private static boolean containsStubMethod(String value) {
        return value.contains("stub") ||
               value.contains("Stub") ||
               value.contains("jni_") ||
               value.contains("_stub") ||
               value.contains("call_stub") ||
               value.contains("adapter");
    }
    
    private static boolean containsPLTReference(String stackTrace) {
        return stackTrace.contains("@plt") ||
               stackTrace.contains(".plt") ||
               stackTrace.contains("PLT") ||
               stackTrace.contains("_plt") ||
               stackTrace.contains("plt_") ||
               stackTrace.contains("dl_runtime") ||
               stackTrace.contains("_dl_fixup");
    }

    private static boolean containsReflectionMethod(String stackTrace) {
        return stackTrace.contains("Method.invoke") ||
               stackTrace.contains("reflect") ||
               stackTrace.contains("NativeMethodAccessor");
    }
    
    private static boolean containsJITReference(String stackTrace) {
        return stackTrace.contains("Compile") ||
               stackTrace.contains("C1") ||
               stackTrace.contains("C2") ||
               stackTrace.contains("OSR") ||
               stackTrace.contains("Tier") ||
               stackTrace.contains("I2C") ||
               stackTrace.contains("C2I") ||
               stackTrace.contains("I2OSR");
    }
    
    private static boolean containsMethodHandleReference(String stackTrace) {
        return stackTrace.contains("MethodHandle") ||
               stackTrace.contains("java.lang.invoke") ||
               stackTrace.contains("LambdaForm") ||
               stackTrace.contains("DirectMethodHandle") ||
               stackTrace.contains("BoundMethodHandle");
    }

    private static boolean containsError(String value) {
        return value.contains(".break_") ||
                value.contains("BCI_ERROR") ||
                value.contains(".invalid_") ||
                value.contains(".unknown()");
    }
}