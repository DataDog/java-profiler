package com.datadoghq.profiler.classgc;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;

import javax.tools.*;
import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.net.URI;
import java.util.Collections;

public class ClassGCTest extends AbstractProfilerTest {



    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms,wall=1ms,filter=0,memleak=524288,cstack=no";
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
        registerCurrentThreadForWallClockProfiling();
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
        long ts = System.nanoTime() + 30_000_000_000L; // 30s timeout
        for (int i = 0; i < 100_000; i++) {
            Class<?> clazz = Class.forName(CLASS_NAME, true, new TestClassLoader(CLASS_NAME, compiledClass));
            MethodHandle consumeCpu = cv.get(clazz);
            consumeCpu.invokeExact();
            if (System.nanoTime() > ts) {
                System.out.println("Timeout (30s). Exitting.");
                break;
            }
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
        compiler.getTask(null, manager, null, null, null, Collections.singletonList(new CharSequenceJavaFileObject(className, code))).call();
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
