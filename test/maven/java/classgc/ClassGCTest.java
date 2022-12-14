package classgc;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.URI;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import javax.tools.FileObject;
import javax.tools.ForwardingJavaFileManager;
import javax.tools.JavaCompiler;
import javax.tools.JavaFileManager;
import javax.tools.SimpleJavaFileObject;
import javax.tools.StandardJavaFileManager;
import javax.tools.ToolProvider;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import one.profiler.JavaProfiler;
import utils.Utils;

public class ClassGCTest {

    private JavaProfiler profiler;
    private Path jfrDump;

    @BeforeEach
    public void setup() throws IOException {
        jfrDump = Files.createTempFile(getClass().getName(), ".jfr");
        profiler = JavaProfiler.getInstance(Utils.getJavaProfilerLib());
        profiler.addThread(profiler.getNativeThreadId());
        profiler.execute("start,cpu=1ms,wall=1ms,filter=0,memleak,jfr,file=" + jfrDump.toAbsolutePath());
    }

    @AfterEach
    public void cleanup() throws IOException {
        profiler.stop();
        Files.deleteIfExists(jfrDump);
    }

    private static final String CLASS_NAME = "code.Worker";
    private static final String JAVA_CODE = "package code;\n" +
            "import java.util.concurrent.ThreadLocalRandom;\n" +
            "\n" +
            "public class Worker {\n" +
            "    public static void consumeCpu() {\n" +
            "        long blackhole = ThreadLocalRandom.current().nextLong();\n" +
            "        for (int i = 0; i < 1000; i++) {\n" +
            "            blackhole ^= ThreadLocalRandom.current().nextLong();\n" +
            "        }\n" +
            "    }\n" +
            "}";

    @Test
    public void profileWithManyShortLivedClasses() throws Throwable {
        // compiles code and loads it with many different classloaders, in the hope that
        // the classes will get GC'd by the time the JFR is dumped
        byte[] compiledClass = compile(CLASS_NAME, JAVA_CODE);
        MethodHandles.Lookup lookup = MethodHandles.publicLookup();
        ClassValue<MethodHandle> cv = new ClassValue<MethodHandle>() {
            @Override
            protected MethodHandle computeValue(Class<?> type) {
                try {
                    return lookup.findStatic(type, "consumeCpu", MethodType.methodType(void.class));
                } catch (Throwable t) {
                    throw new RuntimeException(t);
                }
            }
        };
        for (int i = 0; i < 100_000; i++) {
            Class<?> clazz = Class.forName(CLASS_NAME, true, new TestClassLoader(CLASS_NAME, compiledClass));
            MethodHandle consumeCpu = cv.get(clazz);
            consumeCpu.invokeExact();
        }
    }


    static class TestClassLoader extends ClassLoader {
        private final String className;
        private final byte[] compiledClass;

        public TestClassLoader(String className, byte[] compiledClass) {
            this.className = className;
            this.compiledClass = compiledClass;
        }

        @Override
        public Class<?> loadClass(String name) throws ClassNotFoundException {
            if (name.equals(className)) {
                try {
                    return defineClass(compiledClass, 0, compiledClass.length);
                } catch (Throwable t) {
                    throw new ClassNotFoundException(name);
                }
            }
            return ClassLoader.getSystemClassLoader().loadClass(name);
        }
    }

    // adapted from https://blog.jooq.org/how-to-compile-a-class-at-runtime-with-java-8-and-9/
    private static byte[] compile(String className, String code) {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        ClassFileManager manager = new ClassFileManager(compiler.getStandardFileManager(null, null, null));
        compiler.getTask(null, manager, null, null, null, List.of(new CharSequenceJavaFileObject(className, code))).call();
        return manager.javaFileObject.getBytes();
    }

    private static URI uri(String name, JavaFileObject.Kind kind) {
        return URI.create("string:///" + name.replace('.', '/') + kind.extension);
    }

    static final class JavaFileObject
            extends SimpleJavaFileObject {
        final ByteArrayOutputStream bos = new ByteArrayOutputStream();

        JavaFileObject(String name, JavaFileObject.Kind kind) {
            super(uri(name, kind), kind);
        }

        byte[] getBytes() {
            return bos.toByteArray();
        }

        @Override
        public OutputStream openOutputStream() {
            return bos;
        }
    }

    static final class ClassFileManager extends ForwardingJavaFileManager<StandardJavaFileManager> {
        JavaFileObject javaFileObject;

        ClassFileManager(StandardJavaFileManager m) {
            super(m);
        }

        @Override
        public JavaFileObject getJavaFileForOutput(JavaFileManager.Location location, String className, JavaFileObject.Kind kind, FileObject sibling) {
            return javaFileObject = new JavaFileObject(className, kind);
        }
    }

    static final class CharSequenceJavaFileObject extends SimpleJavaFileObject {
        final CharSequence content;

        public CharSequenceJavaFileObject(String className, CharSequence content) {
            super(uri(className, JavaFileObject.Kind.SOURCE), JavaFileObject.Kind.SOURCE);
            this.content = content;
        }

        @Override
        public CharSequence getCharContent(boolean ignoreEncodingErrors) {
            return content;
        }
    }
}
