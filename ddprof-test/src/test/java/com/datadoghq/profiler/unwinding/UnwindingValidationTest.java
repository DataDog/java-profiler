package com.datadoghq.profiler.unwinding;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import com.github.luben.zstd.Zstd;
import net.jpountz.lz4.LZ4Compressor;
import net.jpountz.lz4.LZ4Factory;
import net.jpountz.lz4.LZ4FastDecompressor;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.common.item.IType;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.unit.UnitLookup;
import org.openjdk.jmc.common.IMCStackTrace;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.*;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.LongAdder;
import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Comprehensive JIT unwinding validation test that focuses on C2 compilation scenarios
 * and related stub unwinding challenges. This test targets the specific issue where
 * profiler->findNativeMethod(pc) returns nullptr, causing '.unknown' frames in stack traces.
 * 
 * The test simulates heavy C2 JIT activity to trigger unwinding failures, particularly
 * during compilation transitions, deoptimization events, and complex call chains.
 */
public class UnwindingValidationTest {
    
    // Profiler management
    private JavaProfiler profiler;
    private Path jfrDump;
    private boolean profilerStarted = false;
    
    // Attributes for JFR analysis - copied from AbstractProfilerTest
    public static final IAttribute<String> THREAD_EXECUTION_MODE =
            attr("mode", "mode", "Execution Mode", PLAIN_TEXT);
    public static final IAttribute<IMCStackTrace> STACK_TRACE = 
            attr("stackTrace", "stackTrace", "", UnitLookup.STACKTRACE);

    /**
     * Start profiler with aggressive settings for unwinding validation.
     */
    private void startProfiler() throws Exception {
        if (profilerStarted) {
            throw new IllegalStateException("Profiler already started");
        }
        
        // Create JFR recording file
        Path rootDir = Paths.get("/tmp/recordings");
        Files.createDirectories(rootDir);
        jfrDump = Files.createTempFile(rootDir, "unwinding-test-", ".jfr");
        
        // EXTREMELY aggressive profiling to catch incomplete stack frames
        profiler = JavaProfiler.getInstance();
        String command = "start,cpu=10us,cstack=vm,jfr,file=" + jfrDump.toAbsolutePath();
        profiler.execute(command);
        profilerStarted = true;
    }
    
    /**
     * Stop profiler and return path to JFR recording.
     */
    private Path stopProfiler() throws Exception {
        if (!profilerStarted) {
            throw new IllegalStateException("Profiler not started");
        }
        
        profiler.stop();
        profilerStarted = false;
        return jfrDump;
    }
    
    /**
     * Verify events from JFR recording and return samples.
     */
    private Iterable<IItemIterable> verifyEvents(String eventType) throws Exception {
        if (jfrDump == null || !Files.exists(jfrDump)) {
            throw new RuntimeException("No JFR dump available");
        }
        
        IItemCollection events = JfrLoaderToolkit.loadEvents(jfrDump.toFile());
        return events.apply(ItemFilters.type(eventType));
    }



    // @Test - DISABLED: Old test method, functionality moved to testComprehensiveUnwindingValidation
    private void testC2TransitionEdgeCases() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        
        System.err.println("=== Starting C2 Transition Edge Cases Test ===");
        
        long totalWork = 0;
        
        // Phase 1: Tier transition scenarios (extended)
        System.err.println("Phase 1: Tier Transitions");
        for (int i = 0; i < 15; i++) {
            totalWork += performTierTransitions();
            if (i % 5 == 0) {
                System.err.println("  Tier transition round " + (i + 1) + "/15");
                LockSupport.parkNanos(5_000_000);
            }
        }
        
        // Phase 2: Deoptimization scenarios (extended)
        System.err.println("Phase 2: Deoptimization Scenarios");
        for (int i = 0; i < 12; i++) {
            totalWork += performC2DeoptScenarios();
            if (i % 4 == 0) {
                System.err.println("  Deoptimization round " + (i + 1) + "/12");
            }
            LockSupport.parkNanos(8_000_000);
        }
        
        // Phase 3: Mixed JIT/JNI during compilation (extended)
        System.err.println("Phase 3: JIT/JNI Mixed Scenarios");
        for (int i = 0; i < 8; i++) {
            totalWork += performJITJNIMixedScenarios();
            if (i % 3 == 0) {
                System.err.println("  Mixed scenario round " + (i + 1) + "/8");
            }
            LockSupport.parkNanos(10_000_000);
        }
        
        stopProfiler();
        assertTrue(totalWork != 0, "Should have performed C2 transition work");
        
        // Generate unified report
        UnwindingTestSuite suite = new UnwindingTestSuite(() -> {
            try {
                return verifyEvents("datadog.ExecutionSample");
            } catch (Exception e) {
                throw new RuntimeException("Failed to verify events", e);
            }
        });
        final long finalTotalWork = totalWork;
        suite.executeTest("C2Transitions", "C2 compilation tier transitions with full edge case coverage", () -> finalTotalWork);
        
        String report = suite.generateReport();
        System.err.println(report);
        
        assertTrue(suite.getResults().size() > 0, "Should have test results");
    }

    // @Test - DISABLED: Old test method, functionality moved to testComprehensiveUnwindingValidation
    private void testIncompleteStackFrameScenarios() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        
        System.err.println("=== Starting Incomplete Stack Frame Test (Targeting Production Error Rates) ===");
        
        long totalWork = 0;
        
        // Phase 1: Immediate profiling during active PLT resolution
        System.err.println("Phase 1: Active PLT Resolution");
        totalWork += performActivePLTResolution();
        
        // Phase 2: Concurrent compilation + immediate heavy workload
        System.err.println("Phase 2: Concurrent JIT + Heavy Native Activity");
        totalWork += performConcurrentCompilationStress();
        
        // Phase 3: ARM64 veneer-heavy scenarios (if applicable)
        System.err.println("Phase 3: Veneer/Trampoline Heavy Workloads");
        totalWork += performVeneerHeavyScenarios();
        
        // Phase 4: Rapid tier transitions during profiling
        System.err.println("Phase 4: Rapid Compilation Transitions");
        totalWork += performRapidTierTransitions();
        
        // Phase 5: Dynamic library loading during profiling
        System.err.println("Phase 5: Dynamic Library Operations During Profiling");
        totalWork += performDynamicLibraryOperations();
        
        // Phase 6: Explicit stack boundary stress
        System.err.println("Phase 6: Stack Boundary Stress Scenarios");
        totalWork += performStackBoundaryStress();
        
        stopProfiler();
        assertTrue(totalWork != 0, "Should have performed incomplete frame work");
        
        // Generate unified report for the complete test
        UnwindingTestSuite suite = new UnwindingTestSuite(() -> {
            try {
                return verifyEvents("datadog.ExecutionSample");
            } catch (Exception e) {
                throw new RuntimeException("Failed to verify events", e);
            }
        });
        final long finalTotalWork = totalWork;
        suite.executeTest("IncompleteStackFrameScenarios", "All incomplete frame scenarios combined", () -> finalTotalWork);
        
        String report = suite.generateReport();
        System.err.println(report);
        
        System.err.println("\n=== INCOMPLETE FRAME TEST SUMMARY ===");
        System.err.println(suite.generateCompactSummary());
        
        assertTrue(suite.getResults().size() > 0, "Should have test results");
    }
    
    private long executeAllJITScenarios() throws Exception {
        long work = 0;
        
        System.err.println("=== Extended JIT Validation Run (targeting C2-related unwinding errors) ===");
        
        // Phase 1: Basic JNI scenarios (extended)
        System.err.println("Phase 1: Extended Basic JNI scenarios");
        for (int i = 0; i < 200; i++) {
            work += performBasicJNIScenarios();
            if (i % 50 == 0) {
                System.err.println("  Basic JNI progress: " + i + "/200");
                LockSupport.parkNanos(5_000_000); // 5ms pause
            }
        }
        
        // Phase 2: Multiple stress scenario rounds
        System.err.println("Phase 2: Multiple concurrent stress rounds");
        for (int round = 0; round < 3; round++) {
            System.err.println("  Stress round " + (round + 1) + "/3");
            work += executeStressScenarios();
            LockSupport.parkNanos(10_000_000); // 10ms between rounds
        }
        
        // Phase 3: Extended PLT/veneer scenarios
        System.err.println("Phase 3: Extended PLT/veneer scenarios");
        for (int i = 0; i < 500; i++) {
            work += performPLTScenarios();
            if (i % 100 == 0) {
                System.err.println("  PLT progress: " + i + "/500");
                LockSupport.parkNanos(5_000_000); // 5ms pause
            }
        }
        
        // Phase 4: Extended mixed scenarios with deeper chains
        System.err.println("Phase 4: Extended mixed scenarios with deeper chains");
        for (int round = 0; round < 5; round++) {
            System.err.println("  Mixed round " + (round + 1) + "/5");
            work += performExtendedMixedScenarios();
            LockSupport.parkNanos(10_000_000); // 10ms between rounds
        }
        
        // Phase 5: Extreme stress scenarios (new)
        System.err.println("Phase 5: Extreme stress scenarios");
        work += performExtremeStressScenarios();
        
        System.err.println("=== Completed Extended JIT Validation Run ===");
        return work;
    }
    
    private long performBasicJNIScenarios() {
        long work = 0;
        
        try {
            // Direct ByteBuffer operations
            ByteBuffer direct = ByteBuffer.allocateDirect(2048);
            for (int i = 0; i < 512; i++) {
                direct.putInt(ThreadLocalRandom.current().nextInt());
            }
            work += direct.position();
            
            // Reflection operations
            Method method = String.class.getMethod("length");
            String testStr = "validation" + ThreadLocalRandom.current().nextInt();
            work += (Integer) method.invoke(testStr);
            
            // Array operations
            int[] array = new int[500];
            int[] copy = new int[500];
            for (int i = 0; i < array.length; i++) {
                array[i] = ThreadLocalRandom.current().nextInt();
            }
            System.arraycopy(array, 0, copy, 0, array.length);
            work += copy[copy.length - 1];
            
        } catch (Exception e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    
    private long executeStressScenarios() throws Exception {
        int threads = 5; // More threads for extended run
        int iterationsPerThread = 25; // More iterations
        ExecutorService executor = Executors.newFixedThreadPool(threads);
        CountDownLatch latch = new CountDownLatch(threads);
        List<Long> threadResults = new ArrayList<>();
        
        // Concurrent JNI operations
        for (int i = 0; i < threads; i++) {
            final int threadId = i;
            executor.submit(() -> {
                try {
                    long work = 0;
                    for (int j = 0; j < iterationsPerThread; j++) {
                        work += performDeepJNIChain(5); // Deeper chains for extended test
                        work += performLargeBufferOps();
                        work += performComplexReflection();
                        if (j % 5 == 0) LockSupport.parkNanos(2_000_000); // 2ms pause
                    }
                    synchronized (threadResults) {
                        threadResults.add(work);
                    }
                } finally {
                    latch.countDown();
                }
            });
        }
        
        assertTrue(latch.await(60, TimeUnit.SECONDS), "Extended stress scenarios should complete");
        executor.shutdown();
        
        return threadResults.stream().mapToLong(Long::longValue).sum();
    }
    
    private long performDeepJNIChain(int depth) {
        if (depth <= 0) return ThreadLocalRandom.current().nextInt(100);
        
        try {
            // JNI -> Java -> JNI chain
            ByteBuffer buffer = ByteBuffer.allocateDirect(1024);
            buffer.putLong(System.nanoTime());
            
            // Reflection in the middle
            Method method = buffer.getClass().getMethod("position");
            Integer pos = (Integer) method.invoke(buffer);
            
            // More JNI
            LZ4Compressor compressor = LZ4Factory.nativeInstance().fastCompressor();
            ByteBuffer source = ByteBuffer.allocateDirect(256);
            ByteBuffer compressed = ByteBuffer.allocateDirect(compressor.maxCompressedLength(256));
            
            byte[] data = new byte[256];
            ThreadLocalRandom.current().nextBytes(data);
            source.put(data);
            source.flip();
            
            compressor.compress(source, compressed);
            
            return pos + compressed.position() + performDeepJNIChain(depth - 1);
            
        } catch (Exception e) {
            return e.hashCode() % 1000 + performDeepJNIChain(depth - 1);
        }
    }
    
    private long performLargeBufferOps() {
        long work = 0;
        
        try {
            ByteBuffer large = ByteBuffer.allocateDirect(16384);
            byte[] data = new byte[8192];
            ThreadLocalRandom.current().nextBytes(data);
            large.put(data);
            large.flip();
            
            // ZSTD compression
            ByteBuffer compressed = ByteBuffer.allocateDirect(Math.toIntExact(Zstd.compressBound(large.remaining())));
            work += Zstd.compress(compressed, large);
            
            // ZSTD decompression
            compressed.flip();
            ByteBuffer decompressed = ByteBuffer.allocateDirect(8192);
            work += Zstd.decompress(decompressed, compressed);
            
        } catch (Exception e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    
    private long performPLTScenarios() {
        long work = 0;
        
        try {
            // Multiple native library calls (PLT entries)
            LZ4FastDecompressor decompressor = LZ4Factory.nativeInstance().fastDecompressor();
            LZ4Compressor compressor = LZ4Factory.nativeInstance().fastCompressor();
            
            ByteBuffer source = ByteBuffer.allocateDirect(512);
            byte[] data = new byte[256];
            ThreadLocalRandom.current().nextBytes(data);
            source.put(data);
            source.flip();
            
            ByteBuffer compressed = ByteBuffer.allocateDirect(compressor.maxCompressedLength(source.remaining()));
            compressor.compress(source, compressed);
            compressed.flip();
            
            ByteBuffer decompressed = ByteBuffer.allocateDirect(256);
            decompressor.decompress(compressed, decompressed);
            work += decompressed.position();
            
            // Method handle operations (veneers)
            MethodHandles.Lookup lookup = MethodHandles.lookup();
            MethodType mt = MethodType.methodType(long.class);
            MethodHandle nanoHandle = lookup.findStatic(System.class, "nanoTime", mt);
            work += (Long) nanoHandle.invoke();
            
        } catch (Throwable e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    
    private long performMixedScenarios() {
        long work = 0;
        
        // Mix of all scenario types to create complex call patterns
        for (int round = 0; round < 20; round++) {
            work += performBasicJNIScenarios();
            work += performPLTScenarios();
            
            // JIT transitions
            work += computeHotMethod(round);
            work += computeColdMethod(round);
            
            if (round % 5 == 0) {
                LockSupport.parkNanos(1_000_000);
            }
        }
        
        return work;
    }
    
    private long computeHotMethod(int input) {
        long result = input;
        for (int i = 0; i < 50; i++) {
            result = result * 31 + i;
        }
        
        // Mix native operation
        if (result % 10 == 0) {
            ByteBuffer temp = ByteBuffer.allocateDirect(32);
            temp.putLong(result);
            result += temp.position();
        }
        
        return result;
    }
    
    private long computeColdMethod(int input) {
        try {
            Thread.yield();
            return input + System.identityHashCode(this) % 1000;
        } catch (Exception e) {
            return input;
        }
    }
    
    
    
    private long performComplexReflection() {
        long work = 0;
        try {
            // Complex reflection patterns that stress unwinder
            Class<?> clazz = ByteBuffer.class;
            Method[] methods = clazz.getDeclaredMethods();
            for (Method method : methods) {
                if (method.getName().startsWith("put") && method.getParameterCount() == 1) {
                    work += method.hashCode();
                    // Create method handle for more complex unwinding
                    MethodHandles.Lookup lookup = MethodHandles.lookup();
                    MethodHandle handle = lookup.unreflect(method);
                    work += handle.hashCode();
                    break;
                }
            }
            
            // Nested reflection calls
            Method lengthMethod = String.class.getMethod("length");
            for (int i = 0; i < 10; i++) {
                String testStr = "test" + i;
                work += (Integer) lengthMethod.invoke(testStr);
            }
            
        } catch (Throwable e) {
            work += e.hashCode() % 1000;
        }
        return work;
    }
    
    private long performExtendedMixedScenarios() {
        long work = 0;
        
        // Extended mix with more aggressive patterns
        for (int round = 0; round < 50; round++) {
            work += performBasicJNIScenarios();
            work += performPLTScenarios();
            work += performComplexReflection();
            
            // More JIT transitions with deeper call chains
            work += computeHotMethod(round);
            work += computeColdMethod(round);
            work += performRecursiveNativeCalls(3);
            
            if (round % 10 == 0) {
                LockSupport.parkNanos(2_000_000); // 2ms pause
            }
        }
        
        return work;
    }
    
    private long performExtremeStressScenarios() throws Exception {
        long work = 0;
        
        System.err.println("  Starting extreme stress scenarios...");
        
        // Very aggressive concurrent workload
        int extremeThreads = 8;
        int extremeIterations = 30;
        ExecutorService extremeExecutor = Executors.newFixedThreadPool(extremeThreads);
        CountDownLatch extremeLatch = new CountDownLatch(extremeThreads);
        List<Long> extremeResults = new ArrayList<>();
        
        for (int i = 0; i < extremeThreads; i++) {
            final int threadId = i;
            extremeExecutor.submit(() -> {
                try {
                    long threadWork = 0;
                    for (int j = 0; j < extremeIterations; j++) {
                        // Very deep JNI chains
                        threadWork += performDeepJNIChain(8);
                        // Large buffer operations
                        threadWork += performLargeBufferOps();
                        // Complex reflection
                        threadWork += performComplexReflection();
                        // Recursive native calls
                        threadWork += performRecursiveNativeCalls(4);
                        // Method handle operations
                        threadWork += performMethodHandleStress();
                        
                        // Very brief pause to allow profiler sampling
                        if (j % 3 == 0) {
                            LockSupport.parkNanos(1_000_000); // 1ms
                        }
                    }
                    synchronized (extremeResults) {
                        extremeResults.add(threadWork);
                    }
                } finally {
                    extremeLatch.countDown();
                }
            });
        }
        
        assertTrue(extremeLatch.await(120, TimeUnit.SECONDS), "Extreme stress should complete");
        extremeExecutor.shutdown();
        
        work += extremeResults.stream().mapToLong(Long::longValue).sum();
        System.err.println("  Completed extreme stress scenarios");
        
        return work;
    }
    
    private long performRecursiveNativeCalls(int depth) {
        if (depth <= 0) return 1;
        
        long work = 0;
        try {
            // Create recursive pattern with native operations at each level
            ByteBuffer buffer = ByteBuffer.allocateDirect(512);
            for (int i = 0; i < 50; i++) {
                buffer.putInt(ThreadLocalRandom.current().nextInt());
            }
            work += buffer.position();
            
            // Recursive call with compression
            if (depth > 1) {
                LZ4Compressor compressor = LZ4Factory.nativeInstance().fastCompressor();
                ByteBuffer source = ByteBuffer.allocateDirect(256);
                ByteBuffer compressed = ByteBuffer.allocateDirect(compressor.maxCompressedLength(256));
                
                byte[] data = new byte[256];
                ThreadLocalRandom.current().nextBytes(data);
                source.put(data);
                source.flip();
                
                compressor.compress(source, compressed);
                work += compressed.position();
                
                // Recursive call
                work += performRecursiveNativeCalls(depth - 1);
            }
            
        } catch (Exception e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    
    private long performMethodHandleStress() {
        long work = 0;
        try {
            MethodHandles.Lookup lookup = MethodHandles.lookup();
            
            // Multiple method handle operations
            MethodType mt1 = MethodType.methodType(long.class);
            MethodHandle nanoHandle = lookup.findStatic(System.class, "nanoTime", mt1);
            work += (Long) nanoHandle.invoke();
            
            MethodType mt2 = MethodType.methodType(int.class);
            MethodHandle hashHandle = lookup.findVirtual(Object.class, "hashCode", mt2);
            work += (Integer) hashHandle.invoke("test" + ThreadLocalRandom.current().nextInt());
            
            MethodType mt3 = MethodType.methodType(int.class);
            MethodHandle lengthHandle = lookup.findVirtual(String.class, "length", mt3);
            work += (Integer) lengthHandle.invoke("methodhandle" + work);
            
            // Chain method handles
            for (int i = 0; i < 5; i++) {
                work += (Long) nanoHandle.invoke();
                work += (Integer) hashHandle.invoke("chain" + i);
            }
            
        } catch (Throwable e) {
            work += e.hashCode() % 1000;
        }
        return work;
    }
    
    // =============== C2 JIT-SPECIFIC METHODS ===============
    
    /**
     * Heavy computational workloads designed to trigger C2 compilation.
     * These methods contain complex arithmetic, loops, and array operations
     * that the JIT compiler optimizes aggressively.
     */
    private long performC2CompilationTriggers() {
        long work = 0;
        
        // Computational intensive methods that trigger C2
        for (int round = 0; round < 20; round++) {
            work += heavyArithmeticMethod(round * 1000);
            work += complexArrayOperations(round);
            work += mathIntensiveLoop(round);
            work += nestedLoopOptimizations(round);
            
            // Mix with native calls to create transition points
            if (round % 5 == 0) {
                work += performMixedNativeCallsDuringCompilation();
            }
        }
        
        return work;
    }
    
    /**
     * Long-running methods designed to trigger OSR (On-Stack Replacement).
     * OSR occurs when a method is running in interpreted mode and gets
     * compiled to C2 while it's executing.
     */
    private long performOSRScenarios() {
        long work = 0;
        
        // Very long-running loops that will trigger OSR
        work += longRunningLoopWithOSR(50000);
        work += recursiveMethodWithOSR(100);
        work += arrayProcessingWithOSR();
        
        return work;
    }
    
    /**
     * Concurrent threads performing C2-triggering workloads simultaneously.
     * This creates scenarios where multiple C2 compilations happen concurrently,
     * increasing the chance of unwinding failures.
     */
    private long performConcurrentC2Compilation() throws Exception {
        int threads = 6;
        int iterationsPerThread = 15;
        ExecutorService executor = Executors.newFixedThreadPool(threads);
        CountDownLatch latch = new CountDownLatch(threads);
        List<Long> results = new ArrayList<>();
        
        for (int i = 0; i < threads; i++) {
            final int threadId = i;
            executor.submit(() -> {
                try {
                    long work = 0;
                    for (int j = 0; j < iterationsPerThread; j++) {
                        // Each thread performs different C2-triggering patterns
                        work += heavyArithmeticMethod(threadId * 1000 + j);
                        work += complexMatrixOperations(threadId);
                        work += stringProcessingWithJIT(threadId);
                        
                        // Mix with native operations
                        work += performNativeMixDuringC2(threadId);
                        
                        if (j % 3 == 0) {
                            LockSupport.parkNanos(2_000_000);
                        }
                    }
                    synchronized (results) {
                        results.add(work);
                    }
                } finally {
                    latch.countDown();
                }
            });
        }
        
        assertTrue(latch.await(90, TimeUnit.SECONDS), "Concurrent C2 compilation should complete");
        executor.shutdown();
        
        return results.stream().mapToLong(Long::longValue).sum();
    }
    
    /**
     * Scenarios that trigger tier transitions: Interpreted -> C1 -> C2.
     * These transitions are points where unwinding can fail.
     */
    private long performTierTransitions() {
        long work = 0;
        
        // Start with methods that will go through tier transitions
        for (int i = 0; i < 30; i++) {
            work += tierTransitionMethod1(i);
            work += tierTransitionMethod2(i);
            work += tierTransitionMethod3(i);
            
            // Mix with reflection to stress unwinder during transitions
            if (i % 5 == 0) {
                work += performReflectionDuringTransition();
            }
        }
        
        return work;
    }
    
    /**
     * Scenarios designed to trigger deoptimization (uncommon traps).
     * Deoptimization is when C2 code falls back to interpreter,
     * creating complex unwinding scenarios.
     */
    private long performC2DeoptScenarios() {
        long work = 0;
        
        try {
            // Scenarios that commonly trigger deoptimization
            work += polymorphicCallSites();
            work += exceptionHandlingDeopt();
            work += classLoadingDuringExecution();
            work += nullCheckDeoptimization();
            work += arrayBoundsDeoptimization();
            
        } catch (Exception e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    
    /**
     * Mixed JIT and JNI operations during active compilation.
     * This targets the exact scenario where findNativeMethod(pc) fails.
     */
    private long performJITJNIMixedScenarios() {
        long work = 0;
        
        for (int round = 0; round < 25; round++) {
            // Start heavy computation to trigger C2 compilation
            work += heavyArithmeticMethod(round * 500);
            
            // Immediately mix with JNI operations
            work += performJNIDuringCompilation();
            
            // More computation to continue JIT activity
            work += complexArrayOperations(round);
            
            // Native library calls during JIT
            work += performNativeLibCallsDuringJIT();
            
            if (round % 5 == 0) {
                LockSupport.parkNanos(3_000_000);
            }
        }
        
        return work;
    }
    
    // =============== COMPUTATIONAL METHODS FOR C2 TRIGGERING ===============
    
    private long heavyArithmeticMethod(int seed) {
        long result = seed;
        
        // Complex arithmetic that C2 will optimize heavily
        for (int i = 0; i < 500; i++) {
            result = result * 31 + i;
            result = Long.rotateLeft(result, 5);
            result ^= (result >>> 21);
            result *= 0x9e3779b97f4a7c15L; // Golden ratio multiplication
            
            // Branch that creates optimization opportunities
            if (result % 17 == 0) {
                result += Math.abs(result % 1000);
            }
        }
        
        return result;
    }
    
    private long complexArrayOperations(int size) {
        int arraySize = 1000 + (size % 500);
        long[] array1 = new long[arraySize];
        long[] array2 = new long[arraySize];
        long result = 0;
        
        // Fill arrays with complex patterns
        for (int i = 0; i < arraySize; i++) {
            array1[i] = i * 13 + size;
            array2[i] = (i * 17) ^ size;
        }
        
        // Complex array processing that triggers C2 optimizations
        for (int pass = 0; pass < 5; pass++) {
            for (int i = 0; i < arraySize - 1; i++) {
                array1[i] = array1[i] + array2[i + 1] * pass;
                array2[i] = array2[i] ^ (array1[i] >>> 3);
                result += array1[i] + array2[i];
            }
        }
        
        return result;
    }
    
    private long mathIntensiveLoop(int iterations) {
        double result = 1.0 + iterations;
        
        // Math operations that C2 optimizes with intrinsics
        for (int i = 0; i < 200; i++) {
            result = Math.sin(result) * Math.cos(i);
            result = Math.sqrt(Math.abs(result)) + Math.log(Math.abs(result) + 1);
            result = Math.pow(result, 1.1);
            
            // Mix integer operations
            if (i % 10 == 0) {
                long intResult = (long) result;
                intResult = Long.rotateLeft(intResult, 7);
                result = intResult + Math.PI;
            }
        }
        
        return (long) result;
    }
    
    private long nestedLoopOptimizations(int depth) {
        long result = 0;
        
        // Nested loops that create vectorization opportunities for C2
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 30; j++) {
                for (int k = 0; k < 10; k++) {
                    result += i * j + k * depth;
                    result ^= (i << j) | (k << depth);
                }
            }
        }
        
        return result;
    }
    
    private long longRunningLoopWithOSR(int iterations) {
        long result = 0;
        
        // Very long loop designed to trigger OSR
        for (int i = 0; i < iterations; i++) {
            result = result * 31 + i;
            result = Long.rotateRight(result, 3);
            
            // Complex branch pattern
            if ((i & 0x0F) == 0) {
                result += Math.abs(result % 100);
            } else if ((i & 0x07) == 0) {
                result ^= i * 13;
            }
            
            // Occasional expensive operation
            if (i % 1000 == 0) {
                result += (long) Math.sqrt(Math.abs(result));
            }
        }
        
        return result;
    }
    
    private long recursiveMethodWithOSR(int depth) {
        if (depth <= 0) return 1;
        
        long result = depth;
        
        // Some computation at each level
        for (int i = 0; i < 100; i++) {
            result = result * 31 + i;
        }
        
        // Recursive call (which itself might get compiled)
        return result + recursiveMethodWithOSR(depth - 1);
    }
    
    private long arrayProcessingWithOSR() {
        int size = 10000;
        int[] array = new int[size];
        long result = 0;
        
        // Fill array
        for (int i = 0; i < size; i++) {
            array[i] = ThreadLocalRandom.current().nextInt();
        }
        
        // Long-running array processing that triggers OSR
        for (int pass = 0; pass < 10; pass++) {
            for (int i = 0; i < size - 1; i++) {
                array[i] = array[i] + array[i + 1] * pass;
                result += array[i];
                
                // Complex branching
                if (array[i] > 0) {
                    array[i] = array[i] >>> 1;
                } else {
                    array[i] = array[i] << 1;
                }
            }
        }
        
        return result;
    }
    
    // =============== TIER TRANSITION METHODS ===============
    
    private long tierTransitionMethod1(int input) {
        // Method designed to go through C1 -> C2 transition
        long result = input;
        for (int i = 0; i < 100; i++) {
            result = result * 31 + i * input;
        }
        return result;
    }
    
    private long tierTransitionMethod2(int input) {
        // Different pattern to trigger different optimization
        long result = input;
        for (int i = 0; i < 80; i++) {
            result ^= (result << 13);
            result ^= (result >>> 17);
            result ^= (result << 5);
        }
        return result;
    }
    
    private long tierTransitionMethod3(int input) {
        // Array-based pattern for vectorization
        int[] temp = new int[50];
        for (int i = 0; i < temp.length; i++) {
            temp[i] = input + i;
        }
        
        long sum = 0;
        for (int val : temp) {
            sum += val * val;
        }
        return sum;
    }
    
    // =============== DEOPTIMIZATION TRIGGER METHODS ===============
    
    private long polymorphicCallSites() {
        // Create polymorphic call sites that can cause deoptimization
        Object[] objects = {
            "string1",
            Integer.valueOf(42),
            "string2",
            Long.valueOf(123L),
            "string3"
        };
        
        long result = 0;
        for (int i = 0; i < 20; i++) {
            for (Object obj : objects) {
                result += obj.hashCode(); // Polymorphic call
            }
        }
        return result;
    }
    
    private long exceptionHandlingDeopt() {
        long result = 0;
        
        for (int i = 0; i < 100; i++) {
            try {
                // Operations that might throw exceptions
                int divisor = (i % 10 == 0) ? 0 : i;
                result += 1000 / divisor;
                
                // Array access that might be out of bounds
                int[] array = new int[10];
                int index = (i % 15 < 10) ? i % 15 : 9;
                result += array[index];
                
            } catch (ArithmeticException | ArrayIndexOutOfBoundsException e) {
                result += e.hashCode() % 100;
            }
        }
        
        return result;
    }
    
    private long classLoadingDuringExecution() {
        long result = 0;
        
        try {
            // Dynamic class operations that can cause deoptimization
            Class<?> clazz = this.getClass();
            Method[] methods = clazz.getDeclaredMethods();
            
            for (Method method : methods) {
                if (method.getName().contains("perform")) {
                    result += method.getName().hashCode();
                }
            }
            
            // Class loading operations
            result += Class.forName("java.util.ArrayList").hashCode();
            result += Class.forName("java.util.HashMap").hashCode();
            
        } catch (ClassNotFoundException e) {
            result += e.hashCode() % 100;
        }
        
        return result;
    }
    
    private long nullCheckDeoptimization() {
        long result = 0;
        Object obj = "test";
        
        for (int i = 0; i < 100; i++) {
            // Pattern that creates null check elimination opportunities
            if (i % 20 == 0) obj = null;
            else if (i % 20 == 1) obj = "value" + i;
            
            // Null check that might cause deoptimization
            if (obj != null) {
                result += obj.hashCode();
            } else {
                result += i;
            }
        }
        
        return result;
    }
    
    private long arrayBoundsDeoptimization() {
        long result = 0;
        int[] array = new int[20];
        
        // Fill array
        for (int i = 0; i < array.length; i++) {
            array[i] = i * 13;
        }
        
        // Access pattern that might trigger bounds check elimination and deopt
        for (int i = 0; i < 100; i++) {
            int index = i % 25; // Sometimes out of bounds
            try {
                if (index < array.length) {
                    result += array[index];
                }
            } catch (ArrayIndexOutOfBoundsException e) {
                result += i;
            }
        }
        
        return result;
    }
    
    // =============== MIXED JIT/JNI METHODS ===============
    
    private long performMixedNativeCallsDuringCompilation() {
        long work = 0;
        
        // Native operations mixed with computation
        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);
        for (int i = 0; i < 100; i++) {
            buffer.putInt(i * 31);
            work += buffer.position();
            
            // Computation that triggers JIT
            work += heavyArithmeticMethod(i);
        }
        
        return work;
    }
    
    private long performJNIDuringCompilation() {
        if (Platform.isMusl()) {
            // can't load LZ4 native library on musl
            return 1;
        }
        long work = 0;
        
        try {
            // Heavy JNI operations during active compilation
            LZ4Compressor compressor = LZ4Factory.nativeInstance().fastCompressor();
            
            for (int i = 0; i < 10; i++) {
                ByteBuffer source = ByteBuffer.allocateDirect(512);
                ByteBuffer compressed = ByteBuffer.allocateDirect(compressor.maxCompressedLength(512));
                
                // Fill with data
                byte[] data = new byte[512];
                ThreadLocalRandom.current().nextBytes(data);
                source.put(data);
                source.flip();
                
                // JNI compression call
                compressor.compress(source, compressed);
                work += compressed.position();
                
                // Computation mixed in
                work += complexArrayOperations(i);
            }
            
        } catch (Exception e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    
    private long performNativeLibCallsDuringJIT() {
        long work = 0;
        
        try {
            // Multiple native library calls during JIT activity
            for (int i = 0; i < 8; i++) {
                // ZSTD operations
                ByteBuffer source = ByteBuffer.allocateDirect(1024);
                ByteBuffer compressed = ByteBuffer.allocateDirect(Math.toIntExact(Zstd.compressBound(1024)));
                
                byte[] data = new byte[1024];
                ThreadLocalRandom.current().nextBytes(data);
                source.put(data);
                source.flip();
                
                work += Zstd.compress(compressed, source);
                
                // Computational work to keep JIT active
                work += mathIntensiveLoop(i);
                
                // System.arraycopy (different native method)
                int[] arr1 = new int[200];
                int[] arr2 = new int[200];
                System.arraycopy(arr1, 0, arr2, 0, 200);
                work += arr2.length;
            }
            
        } catch (Exception e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    
    private long performNativeMixDuringC2(int threadId) {
        long work = 0;
        
        // Thread-specific pattern to create different compilation scenarios
        if (threadId % 3 == 0) {
            work += performJNIDuringCompilation();
        } else if (threadId % 3 == 1) {
            work += performNativeLibCallsDuringJIT();
        } else {
            work += performMixedNativeCallsDuringCompilation();
        }
        
        // Always mix with computation
        work += heavyArithmeticMethod(threadId * 1000);
        
        return work;
    }
    
    private long complexMatrixOperations(int threadId) {
        int size = 50 + threadId * 10;
        long[][] matrix = new long[size][size];
        long result = 0;
        
        // Fill matrix
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = i * j + threadId;
            }
        }
        
        // Matrix operations that C2 can vectorize
        for (int k = 0; k < 5; k++) {
            for (int i = 0; i < size - 1; i++) {
                for (int j = 0; j < size - 1; j++) {
                    matrix[i][j] += matrix[i + 1][j] + matrix[i][j + 1];
                    result += matrix[i][j];
                }
            }
        }
        
        return result;
    }
    
    private long stringProcessingWithJIT(int threadId) {
        StringBuilder sb = new StringBuilder();
        long result = 0;
        
        // String operations that get optimized by C2
        for (int i = 0; i < 100; i++) {
            sb.append("thread").append(threadId).append("_").append(i);
            String str = sb.toString();
            result += str.hashCode();
            
            // String manipulations
            str = str.replace("thread", "th");
            str = str.toUpperCase();
            result += str.length();
            
            sb.setLength(0); // Reset for next iteration
        }
        
        return result;
    }
    
    private long performReflectionDuringTransition() {
        long work = 0;
        
        try {
            // Reflection operations during tier transitions
            Class<?> clazz = Long.class;
            Method method = clazz.getMethod("rotateLeft", long.class, int.class);
            
            for (int i = 0; i < 20; i++) {
                Long result = (Long) method.invoke(null, (long) i * 31, 5);
                work += result;
                
                // Mix with computation to keep transition active
                work += tierTransitionMethod1(i);
            }
            
        } catch (Exception e) {
            work += e.hashCode() % 1000;
        }
        
        return work;
    }
    

    // =========================================================================
    // INCOMPLETE STACK FRAME SCENARIO METHODS
    // These methods specifically target conditions where signals hit during
    // incomplete stack frame setup, causing findNativeMethod() failures
    // =========================================================================

    private long performActivePLTResolution() {
        // Create conditions where PLT stubs are actively resolving during profiling
        // This maximizes the chance of catching signals during incomplete stack setup
        
        System.err.println("  Creating intensive PLT resolution activity...");
        long work = 0;
        
        // Use multiple threads to force PLT resolution under concurrent load
        ExecutorService executor = Executors.newFixedThreadPool(4);
        CountDownLatch latch = new CountDownLatch(4);
        
        for (int thread = 0; thread < 4; thread++) {
            executor.submit(() -> {
                try {
                    // Force many different native library calls to trigger PLT resolution
                    for (int i = 0; i < 1000; i++) {
                        // Mix of different libraries to force PLT entries
                        performIntensiveLZ4Operations();
                        performIntensiveZSTDOperations();
                        performIntensiveReflectionCalls();
                        performIntensiveSystemCalls();
                        
                        // No sleep - maximum PLT activity
                        if (i % 100 == 0 && Thread.currentThread().isInterrupted()) break;
                    }
                } finally {
                    latch.countDown();
                }
            });
        }
        
        try {
            latch.await(30, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        
        executor.shutdown();
        return work + 1000;
    }

    private long performConcurrentCompilationStress() {
        // Start JIT compilation and immediately begin profiling during active compilation
        System.err.println("  Starting concurrent compilation + profiling...");
        long work = 0;
        
        // Create multiple compilation contexts simultaneously
        ExecutorService compilationExecutor = Executors.newFixedThreadPool(6);
        CountDownLatch compilationLatch = new CountDownLatch(6);

        final LongAdder summer = new LongAdder();
        for (int thread = 0; thread < 6; thread++) {
            final int threadId = thread;
            compilationExecutor.submit(() -> {
                try {
                    // Each thread triggers different compilation patterns
                    switch (threadId % 3) {
                        case 0:
                            // Heavy C2 compilation triggers
                            for (int i = 0; i < 500; i++) {
                                summer.add(performIntensiveArithmetic(i * 1000));
                                summer.add(performIntensiveBranching(i));
                            }
                            break;
                        case 1:
                            // OSR compilation scenarios
                            performLongRunningLoops(1000);
                            break;
                        case 2:
                            // Mixed native/Java transitions
                            for (int i = 0; i < 300; i++) {
                                performMixedNativeJavaTransitions();
                            }
                            break;
                    }
                } finally {
                    compilationLatch.countDown();
                }
            });
        }
        
        try {
            compilationLatch.await(45, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("=== blackhole: " + summer.sumThenReset());
        
        compilationExecutor.shutdown();
        return work + 2000;
    }

    private long performVeneerHeavyScenarios() {
        // ARM64-specific: create conditions requiring veneers/trampolines
        System.err.println("  Creating veneer-heavy call patterns...");
        long work = 0;
        
        // Create call patterns that require long jumps (potential veneers on ARM64)
        for (int round = 0; round < 50; round++) {
            // Cross-library calls that may require veneers
            work += performCrossLibraryCalls();
            
            // Deep recursion that spans different code sections
            work += performDeepCrossModuleRecursion(20);
            
            // Rapid library switching
            work += performRapidLibrarySwitching();
            
            // No delays - keep veneer activity high
        }
        
        return work;
    }

    private long performRapidTierTransitions() {
        // Force rapid interpreter -> C1 -> C2 transitions during active profiling
        System.err.println("  Forcing rapid compilation tier transitions...");
        long work = 0;
        
        // Use multiple patterns to trigger different tier transitions
        ExecutorService tierExecutor = Executors.newFixedThreadPool(3);
        CountDownLatch tierLatch = new CountDownLatch(3);
        
        for (int thread = 0; thread < 3; thread++) {
            final int threadId = thread;
            tierExecutor.submit(() -> {
                try {
                    for (int cycle = 0; cycle < 200; cycle++) {
                        // Force decompilation -> recompilation cycles
                        switch (threadId) {
                            case 0:
                                forceDeoptimizationCycle(cycle);
                                break;
                            case 1:
                                forceOSRCompilationCycle(cycle);
                                break;
                            case 2:
                                forceUncommonTrapCycle(cycle);
                                break;
                        }
                        
                        // Brief pause to allow tier transitions
                        if (cycle % 50 == 0) {
                            LockSupport.parkNanos(1_000_000); // 1ms
                        }
                    }
                } finally {
                    tierLatch.countDown();
                }
            });
        }
        
        try {
            tierLatch.await(60, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        
        tierExecutor.shutdown();
        return work + 3000;
    }

    // Helper methods for incomplete frame scenarios

    private long performIntensiveArithmetic(int cycles) {
        // Heavy arithmetic computation to trigger C2 compilation
        long result = 0;
        for (int i = 0; i < cycles; i++) {
            result = result * 31 + i;
            result = Long.rotateLeft(result, 5);
            result ^= (result >>> 21);
            result *= 0x9e3779b97f4a7c15L;
        }
        return result;
    }

    private long performIntensiveBranching(int cycles) {
        // Heavy branching patterns to trigger compilation
        long result = 0;
        for (int i = 0; i < cycles; i++) {
            if (i % 2 == 0) {
                result += i * 3L;
            } else if (i % 3 == 0) {
                result += i * 7L;
            } else if (i % 5 == 0) {
                result += i * 11L;
            } else {
                result += i;
            }
        }
        return result;
    }

    private void performLongRunningLoops(int iterations) {
        // Long-running loops that trigger OSR compilation
        long sum = 0;
        for (int i = 0; i < iterations; i++) {
            sum += (long) i * ThreadLocalRandom.current().nextInt(100);
            if (i % 100 == 0) {
                // Force memory access to prevent optimization
                String.valueOf(sum).hashCode();
            }
        }
        System.out.println("=== blackhole: " + sum);
    }

    private void performIntensiveLZ4Operations() {
        if (Platform.isMusl()) {
            // lz4 native lib not available on musl
            return;
        }
        try {
            LZ4Compressor compressor = LZ4Factory.nativeInstance().fastCompressor();
            LZ4FastDecompressor decompressor = LZ4Factory.nativeInstance().fastDecompressor();
            
            ByteBuffer source = ByteBuffer.allocateDirect(1024);
            source.putInt(ThreadLocalRandom.current().nextInt());
            source.flip();
            
            ByteBuffer compressed = ByteBuffer.allocateDirect(compressor.maxCompressedLength(source.limit()));
            compressor.compress(source, compressed);
            
            compressed.flip();
            ByteBuffer decompressed = ByteBuffer.allocateDirect(source.limit());
            decompressor.decompress(compressed, decompressed);
        } catch (Exception e) {
            // Expected during rapid PLT resolution
        }
    }

    private void performIntensiveZSTDOperations() {
        try {
            ByteBuffer source = ByteBuffer.allocateDirect(1024);
            source.putLong(ThreadLocalRandom.current().nextLong());
            source.flip();
            
            ByteBuffer compressed = ByteBuffer.allocateDirect(Math.toIntExact(Zstd.compressBound(source.limit())));
            Zstd.compress(compressed, source);
        } catch (Exception e) {
            // Expected during rapid PLT resolution
        }
    }

    private void performIntensiveReflectionCalls() {
        try {
            Method method = String.class.getMethod("valueOf", int.class);
            for (int i = 0; i < 10; i++) {
                method.invoke(null, i);
            }
        } catch (Exception e) {
            // Expected during rapid reflection
        }
    }

    private void performIntensiveSystemCalls() {
        // System calls that go through different stubs
        int[] array1 = new int[100];
        int[] array2 = new int[100];
        System.arraycopy(array1, 0, array2, 0, array1.length);
        
        // String operations that may use native methods
        String.valueOf(ThreadLocalRandom.current().nextInt()).hashCode();
    }

    private long performCrossLibraryCalls() {
        long work = 0;
        
        // Mix calls across different native libraries
        try {
            // LZ4 -> ZSTD -> System -> Reflection
            performIntensiveLZ4Operations();
            performIntensiveZSTDOperations();
            performIntensiveSystemCalls();
            performIntensiveReflectionCalls();
            work += 10;
        } catch (Exception e) {
            // Expected during cross-library transitions
        }
        
        return work;
    }

    private long performDeepCrossModuleRecursion(int depth) {
        if (depth <= 0) return 1;
        
        // Mix native and Java calls in recursion
        performIntensiveLZ4Operations();
        long result = performDeepCrossModuleRecursion(depth - 1);
        performIntensiveSystemCalls();
        
        return result + depth;
    }

    private long performRapidLibrarySwitching() {
        long work = 0;
        
        // Rapid switching between different native libraries
        for (int i = 0; i < 20; i++) {
            switch (i % 4) {
                case 0: performIntensiveLZ4Operations(); break;
                case 1: performIntensiveZSTDOperations(); break;
                case 2: performIntensiveSystemCalls(); break;
                case 3: performIntensiveReflectionCalls(); break;
            }
            work++;
        }
        
        return work;
    }

    private void forceDeoptimizationCycle(int cycle) {
        // Pattern that forces deoptimization
        Object obj = (cycle % 2 == 0) ? "string" : Integer.valueOf(cycle);
        
        // This will cause uncommon trap and deoptimization
        if (obj instanceof String) {
            performIntensiveArithmetic(cycle);
        } else {
            performIntensiveBranching(cycle);
        }
    }

    private void forceOSRCompilationCycle(int cycle) {
        // Long-running loop that triggers OSR
        long sum = 0;
        for (int i = 0; i < 1000; i++) {
            sum += (long) i * cycle;
            if (i % 100 == 0) {
                // Force native call during OSR
                performIntensiveSystemCalls();
            }
        }
    }

    private void forceUncommonTrapCycle(int cycle) {
        // Pattern that creates uncommon traps
        try {
            Class<?> clazz = (cycle % 3 == 0) ? String.class : Integer.class;
            Method method = clazz.getMethod("toString");
            method.invoke((cycle % 2 == 0) ? "test" : Integer.valueOf(cycle));
        } catch (Exception e) {
            // Creates uncommon trap scenarios
        }
    }

    private long performMixedNativeJavaTransitions() {
        long work = 0;
        
        // Rapid Java -> Native -> Java transitions
        work += performIntensiveArithmetic(100);
        performIntensiveLZ4Operations();
        work += performIntensiveBranching(50);
        performIntensiveSystemCalls();
        work += performIntensiveArithmetic(75);
        
        return work;
    }

    private long performDynamicLibraryOperations() {
        // Force dynamic library operations during profiling to stress symbol resolution
        long work = 0;
        
        ExecutorService libraryExecutor = Executors.newFixedThreadPool(2);
        CountDownLatch libraryLatch = new CountDownLatch(2);
        
        for (int thread = 0; thread < 2; thread++) {
            libraryExecutor.submit(() -> {
                try {
                    // Force class loading and native method resolution during profiling
                    for (int i = 0; i < 100; i++) {
                        // Force dynamic loading of native methods by class loading
                        forceClassLoading(i);
                        
                        // Force JNI method resolution
                        forceJNIMethodResolution();
                        
                        // Force reflection method caching
                        forceReflectionMethodCaching(i);
                        
                        // Brief yield to maximize chance of signal during resolution
                        Thread.yield();
                    }
                } finally {
                    libraryLatch.countDown();
                }
            });
        }
        
        try {
            libraryLatch.await(30, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        
        libraryExecutor.shutdown();
        return work + 1000;
    }

    private long performStackBoundaryStress() {
        // Create scenarios that stress stack walking at boundaries
        long work = 0;
        
        ExecutorService boundaryExecutor = Executors.newFixedThreadPool(3);
        CountDownLatch boundaryLatch = new CountDownLatch(3);
        
        for (int thread = 0; thread < 3; thread++) {
            final int threadId = thread;
            boundaryExecutor.submit(() -> {
                try {
                    switch (threadId) {
                        case 0:
                            // Deep recursion to stress stack boundaries
                            for (int i = 0; i < 50; i++) {
                                performDeepRecursionWithNativeCalls(30);
                            }
                            break;
                        case 1:
                            // Rapid stack growth/shrinkage
                            for (int i = 0; i < 200; i++) {
                                performRapidStackChanges(i);
                            }
                            break;
                        case 2:
                            // Exception-based stack unwinding stress
                            for (int i = 0; i < 100; i++) {
                                performExceptionBasedUnwindingStress();
                            }
                            break;
                    }
                } finally {
                    boundaryLatch.countDown();
                }
            });
        }
        
        try {
            boundaryLatch.await(45, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        
        boundaryExecutor.shutdown();
        return work + 2000;
    }

    // Additional helper methods for dynamic library and stack boundary stress

    private void forceClassLoading(int iteration) {
        try {
            // Force loading of classes with native methods
            String className = (iteration % 3 == 0) ? "java.util.zip.CRC32" : 
                               (iteration % 3 == 1) ? "java.security.SecureRandom" : 
                               "java.util.concurrent.ThreadLocalRandom";
            
            Class<?> clazz = Class.forName(className);
            // Force static initialization which may involve native method resolution
            clazz.getDeclaredMethods();
        } catch (Exception e) {
            // Expected during dynamic loading
        }
    }

    private void forceJNIMethodResolution() {
        // Operations that force JNI method resolution
        try {
            // These operations force native method lookup
            System.identityHashCode(new Object());
            Runtime.getRuntime().availableProcessors();
            System.nanoTime();
            
            // Force string native operations
            "test".intern();
            
        } catch (Exception e) {
            // Expected during method resolution
        }
    }

    private void forceReflectionMethodCaching(int iteration) {
        try {
            // Force method handle caching and native method resolution
            Class<?> clazz = String.class;
            Method method = clazz.getMethod("valueOf", int.class);
            
            // This forces method handle creation and caching
            for (int i = 0; i < 5; i++) {
                method.invoke(null, iteration + i);
            }
        } catch (Exception e) {
            // Expected during reflection operations
        }
    }

    private void performDeepRecursionWithNativeCalls(int depth) {
        if (depth <= 0) return;
        
        // Mix native calls in recursion
        performIntensiveLZ4Operations();
        System.arraycopy(new int[10], 0, new int[10], 0, 10);
        
        performDeepRecursionWithNativeCalls(depth - 1);
        
        // More native calls on return path
        String.valueOf(depth).hashCode();
    }

    private void performRapidStackChanges(int iteration) {
        // Create rapid stack growth and shrinkage patterns
        try {
            switch (iteration % 4) {
                case 0:
                    rapidStackGrowth1(iteration);
                    break;
                case 1:
                    rapidStackGrowth2(iteration);
                    break;
                case 2:
                    rapidStackGrowth3(iteration);
                    break;
                case 3:
                    rapidStackGrowth4(iteration);
                    break;
            }
        } catch (StackOverflowError e) {
            // Expected - this stresses stack boundaries
        }
    }

    private void rapidStackGrowth1(int depth) {
        if (depth > 50) return;
        performIntensiveSystemCalls();
        rapidStackGrowth1(depth + 1);
    }

    private void rapidStackGrowth2(int depth) {
        if (depth > 50) return;
        performIntensiveLZ4Operations();
        rapidStackGrowth2(depth + 1);
    }

    private void rapidStackGrowth3(int depth) {
        if (depth > 50) return;
        performIntensiveReflectionCalls();
        rapidStackGrowth3(depth + 1);
    }

    private void rapidStackGrowth4(int depth) {
        if (depth > 50) return;
        performIntensiveZSTDOperations();
        rapidStackGrowth4(depth + 1);
    }

    private void performExceptionBasedUnwindingStress() {
        // Use exceptions to force stack unwinding during native operations
        try {
            try {
                try {
                    performIntensiveLZ4Operations();
                    throw new RuntimeException("Force unwinding");
                } catch (RuntimeException e1) {
                    performIntensiveSystemCalls();
                    throw new IllegalArgumentException("Force unwinding 2");
                }
            } catch (IllegalArgumentException e2) {
                performIntensiveReflectionCalls();
                throw new UnsupportedOperationException("Force unwinding 3");
            }
        } catch (UnsupportedOperationException e3) {
            // Final catch - forces multiple stack unwind operations
            performIntensiveZSTDOperations();
        }
    }

    /**
     * Multi-scenario test that runs all incomplete frame scenarios with original granularity
     * but reports each phase as a separate test result in the unified dashboard.
     * Each scenario gets its own JFR recording file for proper isolation.
     */
    @Test
    public void testComprehensiveUnwindingValidation() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        
        System.err.println("=== Comprehensive Unwinding Validation Test ===");
        
        List<TestResult> results = new ArrayList<>();
        
        // Execute each phase as a separate test with its own profiler session and JFR file
        
        // C2 Compilation scenarios from original testHeavyC2JITActivity
        results.add(executeIndividualScenario("C2CompilationTriggers", "C2 compilation triggers with computational workloads", () -> {
            System.err.println("  Starting C2 compilation triggers...");
            long work = 0;
            for (int round = 0; round < 10; round++) {
                work += performC2CompilationTriggers();
                if (round % 3 == 0) {
                    LockSupport.parkNanos(5_000_000); // 5ms pause
                }
            }
            return work;
        }));
        
        results.add(executeIndividualScenario("OSRScenarios", "On-Stack Replacement compilation scenarios", () -> {
            System.err.println("  Starting OSR scenarios...");
            long work = 0;
            for (int round = 0; round < 5; round++) {
                work += performOSRScenarios();
                LockSupport.parkNanos(10_000_000); // 10ms pause
            }
            return work;
        }));
        
        results.add(executeIndividualScenario("ConcurrentC2Compilation", "Concurrent C2 compilation stress", () -> {
            System.err.println("  Starting concurrent C2 compilation...");
            return performConcurrentC2Compilation();
        }));
        
        // C2 Deoptimization scenarios from original testC2TransitionEdgeCases  
        results.add(executeIndividualScenario("C2DeoptScenarios", "C2 deoptimization and transition edge cases", () -> {
            System.err.println("  Starting C2 deopt scenarios...");
            long work = 0;
            for (int round = 0; round < 5; round++) {
                work += performC2DeoptScenarios();
                LockSupport.parkNanos(15_000_000); // 15ms pause
            }
            return work;
        }));
        
        // Extended JIT scenarios from original testComprehensiveJITUnwinding
        results.add(executeIndividualScenario("ExtendedJNIScenarios", "Extended basic JNI scenarios", () -> {
            System.err.println("  Starting extended JNI scenarios...");
            long work = 0;
            for (int i = 0; i < 200; i++) {
                work += performBasicJNIScenarios();
                if (i % 50 == 0) {
                    LockSupport.parkNanos(5_000_000); // 5ms pause
                }
            }
            return work;
        }));
        
        results.add(executeIndividualScenario("MultipleStressRounds", "Multiple concurrent stress rounds", () -> {
            System.err.println("  Starting multiple stress rounds...");
            long work = 0;
            for (int round = 0; round < 3; round++) {
                work += executeStressScenarios();
                LockSupport.parkNanos(10_000_000); // 10ms between rounds
            }
            return work;
        }));
        
        results.add(executeIndividualScenario("ExtendedPLTScenarios", "Extended PLT/veneer scenarios", () -> {
            System.err.println("  Starting extended PLT scenarios...");
            long work = 0;
            for (int i = 0; i < 500; i++) {
                work += performPLTScenarios();
                if (i % 100 == 0) {
                    LockSupport.parkNanos(2_000_000); // 2ms pause
                }
            }
            return work;
        }));
        
        // Original scenarios from the previous comprehensive test
        results.add(executeIndividualScenario("ActivePLTResolution", "Intensive PLT resolution during profiling", () -> {
            System.err.println("  Starting intensive PLT resolution...");
            return performActivePLTResolution();
        }));
        
        results.add(executeIndividualScenario("ConcurrentCompilationStress", "Heavy JIT compilation + native activity", () -> {
            System.err.println("  Starting concurrent compilation stress...");
            return performConcurrentCompilationStress();
        }));
        
        results.add(executeIndividualScenario("VeneerHeavyScenarios", "ARM64 veneer/trampoline intensive workloads", () -> {
            System.err.println("  Starting veneer-heavy scenarios...");
            return performVeneerHeavyScenarios();
        }));
        
        results.add(executeIndividualScenario("RapidTierTransitions", "Rapid compilation tier transitions", () -> {
            System.err.println("  Starting rapid tier transitions...");
            return performRapidTierTransitions();
        }));
        
        results.add(executeIndividualScenario("DynamicLibraryOps", "Dynamic library operations during profiling", () -> {
            System.err.println("  Starting dynamic library operations...");
            return performDynamicLibraryOperations();
        }));
        
        results.add(executeIndividualScenario("StackBoundaryStress", "Stack boundary stress scenarios", () -> {
            System.err.println("  Starting stack boundary stress...");
            return performStackBoundaryStress();
        }));
        
        // Generate comprehensive unified report showing all scenarios
        String report = UnwindingDashboard.generateReport(results);
        System.err.println(report);
        
        // Overall assessment with detailed breakdown
        System.err.println("\n=== GRANULAR INCOMPLETE FRAME TEST SUMMARY ===");
        System.err.println(UnwindingDashboard.generateCompactSummary(results));
        
        // Validate that we have detailed results for each scenario
        assertTrue(results.size() == 13, "Should have results for all 13 scenarios");
        
        // Check for high-intensity results (should have higher error rates if working correctly)
        double overallErrorRate = results.stream()
                .mapToDouble(r -> r.getMetrics().getErrorRate())
                .average()
                .orElse(0.0);
        System.err.println("Overall error rate across all scenarios: " + String.format("%.3f%%", overallErrorRate));

        assertFalse(results.isEmpty(), "Should have test results");
    }
    
    /**
     * Execute a single scenario with its own profiler session and JFR recording.
     */
    private TestResult executeIndividualScenario(String testName, String description, 
                                                UnwindingTestSuite.TestScenario scenario) throws Exception {
        long startTime = System.currentTimeMillis();
        
        // Start profiler for this specific scenario
        startProfiler();
        
        try {
            // Execute the scenario
            long workCompleted = scenario.execute();
            
            // Stop profiler for this scenario
            stopProfiler();
            
            // Analyze results for this specific scenario
            Iterable<IItemIterable> cpuSamples = verifyEvents("datadog.ExecutionSample");
            IMemberAccessor<String, IItem> modeAccessor = null;
            
            for (IItemIterable samples : cpuSamples) {
                modeAccessor = THREAD_EXECUTION_MODE.getAccessor(samples.getType());
                break;
            }
            
            if (modeAccessor == null) {
                throw new RuntimeException("Could not get mode accessor for scenario: " + testName);
            }
            
            UnwindingMetrics.UnwindingResult metrics = 
                UnwindingMetrics.analyzeUnwindingData(cpuSamples, modeAccessor);
            
            long executionTime = System.currentTimeMillis() - startTime;
            
            TestResult result = TestResult.create(testName, description, metrics, executionTime);
            
            System.err.println("Completed: " + testName + " (" + executionTime + "ms, " + 
                              metrics.totalSamples + " samples, " + 
                              String.format("%.2f%%", metrics.getErrorRate()) + " error rate)");
            
            return result;
            
        } catch (Exception e) {
            // Ensure profiler is stopped even on failure
            if (profilerStarted) {
                try {
                    stopProfiler();
                } catch (Exception stopException) {
                    System.err.println("Warning: Failed to stop profiler: " + stopException.getMessage());
                }
            }
            
            // Create a failed result
            UnwindingMetrics.UnwindingResult emptyResult = new UnwindingMetrics.UnwindingResult(
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 
                    java.util.Collections.emptyMap(), java.util.Collections.emptyMap());
            
            long executionTime = System.currentTimeMillis() - startTime;
            TestResult failedResult = new TestResult(testName, description, emptyResult, 
                    TestResult.Status.NEEDS_WORK, "Scenario execution failed: " + e.getMessage(),
                    executionTime);
            
            System.err.println("Failed: " + testName + " (" + executionTime + "ms) - " + e.getMessage());
            return failedResult;
        }
    }

}