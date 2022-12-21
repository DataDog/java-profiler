package com.datadoghq.profiler.wallclock;

import one.profiler.JavaProfiler;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Optional;
import java.util.function.LongSupplier;

public class Tracing {

    private static final ThreadLocal<Tracing> STACK = ThreadLocal.withInitial(Tracing::new);

    public static Context newContext(LongSupplier idSupplier, JavaProfiler profiler) {
        return STACK.get().create(idSupplier, profiler);
    }

    public static MigratingContext capture() {
        return STACK.get().startMigration();
    }

    private final Deque<Context> stack = new ArrayDeque<>();

    private Context create(LongSupplier supplier, JavaProfiler profiler) {
        long id = supplier.getAsLong();
        long rootSpanId = Optional.ofNullable(stack.peekLast()).map(Context::getRootSpanId).orElse(id);
        Context context = new Context(profiler, stack, rootSpanId, id);
        stack.addFirst(context);
        return context;
    }

    public MigratingContext startMigration() {
        return Optional.ofNullable(stack.peekFirst()).map(Context::snapshot).orElse(null);
    }

    Context endMigration(MigratingContext context) {
        Context activated = new Context(this.stack, context);
        stack.addFirst(activated);
        return activated;
    }

    public static class MigratingContext {

        private final JavaProfiler profiler;
        private final long rootSpanId;
        private final long spanId;

        public MigratingContext(JavaProfiler profiler, long rootSpanId, long spanId) {
            this.profiler = profiler;
            this.rootSpanId = rootSpanId;
            this.spanId = spanId;
        }

        public Context activate() {
            Context context = STACK.get().endMigration(this);
            context.notifyProfiler();
            return context;
        }
    }

    public static class Context implements AutoCloseable {

        private final JavaProfiler profiler;
        private final Deque<Context> stack;
        private final long rootSpanId;
        private final long spanId;

        public Context(Deque<Context> stack, MigratingContext context) {
            this(context.profiler, stack, context.rootSpanId, context.spanId);
        }

        public Context(JavaProfiler profiler, Deque<Context> stack, long rootSpanId, long spanId) {
            this.stack = stack;
            this.rootSpanId = rootSpanId;
            this.spanId = spanId;
            this.profiler = profiler;
            notifyProfiler();
        }

        public MigratingContext snapshot() {
            return new MigratingContext(profiler, rootSpanId, spanId);
        }

        private void notifyProfiler() {
            profiler.setContext(spanId, rootSpanId);
        }

        public long getRootSpanId() {
            return rootSpanId;
        }

        public long getSpanId() {
            return spanId;
        }

        @Override
        public void close() {
            if (stack != null) {
                Context top = stack.removeFirst();
                assert top == this : "expected " + this + " on stack but have " + top;
                Optional.ofNullable(stack.peekFirst()).ifPresent(Context::notifyProfiler);
            }
        }


        @Override
        public String toString() {
            return "Context{" +
                    "rootSpanId=" + rootSpanId +
                    ", spanId=" + spanId +
                    '}';
        }
    }
}
