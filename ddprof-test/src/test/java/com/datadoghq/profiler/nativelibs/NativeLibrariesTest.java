package com.datadoghq.profiler.nativelibs;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.github.luben.zstd.Zstd;
import net.jpountz.lz4.LZ4Compressor;
import net.jpountz.lz4.LZ4Factory;
import net.jpountz.lz4.LZ4FastDecompressor;
import net.jpountz.lz4.LZ4SafeDecompressor;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;
import org.xerial.snappy.Snappy;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.BiConsumer;
import java.util.function.IntFunction;
import java.util.function.ToIntFunction;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Loads and calls into widely used native libraries
 *
 * we should be able to parse the dwarf info section of these common libraries on linux without segfaulting
 * and we should be able to unwind the native stacks
 * */
public class NativeLibrariesTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms,cstack=" + (Platform.isMac() ? "fp" : "dwarf");
    }

    @Test
    public void test() {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        boolean isMusl = Optional.ofNullable(System.getenv("TEST_CONFIGURATION")).orElse("").startsWith("musl");
        int blackhole = 0;
        for (int i = 0; i < 100; i++) {
            blackhole ^= lz4Java();
        }
        for (int i = 0; i < 100; i++) {
            blackhole ^= zstdJni();
        }
        // snappy-java may not load under musl
        if (!isMusl) {
            for (int i = 0; i < 100; i++) {
                blackhole ^= snappyJava();
            }
        }
        stopProfiler();
        assertTrue(blackhole != 0);
        Map<String, AtomicInteger> modeCounters = new HashMap<>();
        Map<String, AtomicInteger> libraryCounters = new HashMap<>();
        for (IItemIterable cpuSamples : verifyEvents("datadog.ExecutionSample")) {
            IMemberAccessor<String, IItem> stacktraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            IMemberAccessor<String, IItem> modeAccessor = THREAD_EXECUTION_MODE.getAccessor(cpuSamples.getType());
            for (IItem item : cpuSamples) {
                String stacktrace = stacktraceAccessor.getMember(item);
                String mode = modeAccessor.getMember(item);
                modeCounters.computeIfAbsent(mode, x -> new AtomicInteger()).incrementAndGet();
                if ("NATIVE".equals(mode)) {
                    String library = "";
                    if (stacktrace.contains("net_jpountz_lz4_LZ4JNI")) {
                        library = "LZ4";
                    } else if (stacktrace.contains("Java_org_xerial_snappy_SnappyNative")) {
                        library = "SNAPPY";
                    } else if (stacktrace.contains("Java_com_github_luben_zstd")) {
                        library = "ZSTD";
                    } else if (stacktrace.contains("Compile")) {
                        library = "JIT";
                    }
                    libraryCounters.computeIfAbsent(library, x -> new AtomicInteger()).incrementAndGet();
                }
            }
        }
        assertTrue(modeCounters.containsKey("JVM"), "no JVM samples");
        assertTrue(modeCounters.containsKey("NATIVE"), "no NATIVE samples");
        assertTrue(Platform.isMac() || libraryCounters.containsKey("LZ4"), "no lz4-java samples");
        // looks like we might drop these samples with FP unwinding (which we have to use on MacOS)
        // flaky
        // assertTrue(isMusl || Platform.isMac() || libraryCounters.containsKey("SNAPPY"), "no snappy-java samples");
        // cannot unwind these samples with FP unwinding (which we have to use on MacOS)
        assertTrue(Platform.isMac() || libraryCounters.containsKey("ZSTD"), "no zstd-jni samples");
        modeCounters.forEach((mode, count) -> System.err.println(mode + ": " + count.get()));
        libraryCounters.forEach((lib, count) -> System.err.println(lib + ": " + count.get()));
    }


    private int lz4Java() {
        LZ4FastDecompressor fastDecompressor = LZ4Factory.nativeInstance().fastDecompressor();
        LZ4SafeDecompressor safeDecompressor = LZ4Factory.nativeInstance().safeDecompressor();
        LZ4Compressor fastCompressor = LZ4Factory.nativeInstance().fastCompressor();
        LZ4Compressor highCompressor = LZ4Factory.nativeInstance().highCompressor();
        int blackhole =  ThreadLocalRandom.current().nextInt();
        blackhole ^= roundTrip(fill(ByteBuffer.allocateDirect(256 << 10)),
                bb -> fastCompressor.maxCompressedLength(bb.limit()),
                ByteBuffer::allocateDirect,
                fastCompressor::compress,
                fastDecompressor::decompress);
        blackhole ^= roundTrip(fill(ByteBuffer.allocate(256 << 10)),
                bb -> fastCompressor.maxCompressedLength(bb.limit()),
                ByteBuffer::allocate,
                fastCompressor::compress,
                fastDecompressor::decompress);
        blackhole ^= roundTrip(fill(ByteBuffer.allocateDirect(256 << 10)),
                bb -> 2 * bb.limit(),
                ByteBuffer::allocateDirect,
                fastCompressor::compress,
                safeDecompressor::decompress);
        blackhole ^= roundTrip(fill(ByteBuffer.allocate(256 << 10)),
                bb -> 2 * bb.limit(),
                ByteBuffer::allocate,
                fastCompressor::compress,
                safeDecompressor::decompress);
        blackhole ^= roundTrip(fill(ByteBuffer.allocateDirect(256 << 10)),
                bb -> fastCompressor.maxCompressedLength(bb.limit()),
                ByteBuffer::allocateDirect,
                highCompressor::compress,
                fastDecompressor::decompress);
        blackhole ^= roundTrip(fill(ByteBuffer.allocate(256 << 10)),
                bb -> fastCompressor.maxCompressedLength(bb.limit()),
                ByteBuffer::allocate,
                highCompressor::compress,
                fastDecompressor::decompress);
        blackhole ^= roundTrip(fill(ByteBuffer.allocateDirect(256 << 10)),
                bb -> 2 * bb.limit(),
                ByteBuffer::allocateDirect,
                highCompressor::compress,
                safeDecompressor::decompress);
        blackhole ^= roundTrip(fill(ByteBuffer.allocate(256 << 10)),
                bb -> 2 * bb.limit(),
                ByteBuffer::allocate,
                highCompressor::compress,
                safeDecompressor::decompress);
        return blackhole;
    }

    private int zstdJni() {
        int blackhole = 0;
        for (int i = 0; i < 20; i++) {
            blackhole ^= roundTrip(fill(ByteBuffer.allocateDirect(256 << 10)),
                    bb -> Math.toIntExact(Zstd.compressBound(bb.limit())),
                    ByteBuffer::allocateDirect,
                    (source, dest) -> {
                        int limit = Zstd.compress(dest, source);
                        dest.position(limit);
                    },
                    (source, dest) -> {
                        int limit = Zstd.decompress(dest, source);
                        dest.position(limit);
                    });
        }
        return blackhole;
    }

    private int snappyJava() {
        int blackhole = 0;
        for (int i = 0; i < 10; i++) {
            blackhole ^= roundTrip(fill(ByteBuffer.allocateDirect(256 << 10)),
                    bb -> Snappy.maxCompressedLength(bb.limit()),
                    ByteBuffer::allocateDirect,
                    (source, dest) -> {
                        try {
                            int limit = Snappy.compress(source, dest);
                            dest.position(limit);
                        } catch (IOException e) {
                            e.printStackTrace(System.err);
                        }
                    },
                    (source, dest) -> {
                        try {
                            int limit = Snappy.uncompress(source, dest);
                            dest.position(limit);
                        } catch (IOException e) {
                            e.printStackTrace(System.err);
                        }
                    });
        }
        return blackhole;
    }

    ByteBuffer fill(ByteBuffer buffer) {
        byte[] bytes = new byte[buffer.limit()];
        ThreadLocalRandom.current().nextBytes(bytes);
        buffer.mark();
        buffer.put(bytes);
        buffer.reset();
        return buffer;
    }

    private int roundTrip(ByteBuffer data,
                           ToIntFunction<ByteBuffer> maxCompressedSizer,
                           IntFunction<ByteBuffer> compressedBufferSupplier,
                           BiConsumer<ByteBuffer, ByteBuffer> compress,
                           BiConsumer<ByteBuffer, ByteBuffer> decompress) {
        int maxCompressedSize = maxCompressedSizer.applyAsInt(data);
        ByteBuffer compressedBuffer = compressedBufferSupplier.apply(maxCompressedSize);
        ByteBuffer targetBuffer = compressedBufferSupplier.apply(data.limit());
        compress.accept(data, compressedBuffer);
        compressedBuffer.flip();
        decompress.accept(compressedBuffer, targetBuffer);
        return targetBuffer.position();
    }
}
