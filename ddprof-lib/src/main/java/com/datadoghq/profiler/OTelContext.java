package com.datadoghq.profiler;

import java.util.Objects;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.function.Consumer;

/**
 * OpenTelemetry Process Context API for sharing process-level context information.
 * 
 * <p>This class provides functionality to publish OpenTelemetry semantic conventions
 * compliant process context information that can be discovered and read by external
 * monitoring tools and profilers. The context is shared via platform-specific
 * mechanisms (currently Linux-only) and includes service identification metadata.
 * 
 * <p><b>Platform Support:</b>
 * <ul>
 *   <li><b>Linux:</b> Full support using anonymous memory mappings with prctl naming</li>
 *   <li><b>Others:</b> Limited support - API calls are no-ops</li>
 * </ul>
 * 
 * <p><b>Thread Safety:</b> This class is thread-safe. All public methods can be
 * called concurrently from multiple threads.
 * 
 * <p><b>Usage Example:</b>
 * <pre>{@code
 * // Get the singleton instance
 * OTelContext context = OTelContext.getInstance();
 * 
 * // Set process context for external discovery
 * context.initializeAllContext(...);
 * }</pre>
 * 
 * <p><b>External Discovery:</b> Once published, the process context can be
 * discovered by external tools by scanning /proc/&#42;/maps for mappings named
 * &#91;anon:OTEL_CTX&#93; on Linux systems.
 * 
 * @since 1.30.0
 */
public final class OTelContext {
    private static final class SingletonHolder {
        static final OTelContext INSTANCE = new OTelContext();
    }

    /**
     * Represents the OpenTelemetry process context data.
     */
    public static final class ProcessContext {
        public final String deploymentEnvironmentName;
        public final String hostName;
        public final String serviceInstanceId;
        public final String serviceName;
        public final String serviceVersion;
        public final String telemetrySdkLanguage;
        public final String telemetrySdkVersion;
        public final String telemetrySdkName;
        /**
         * The threadlocal.attribute_key_map published in the process context's
         * thread_ctx_config, or null if no thread context configuration was
         * published. The first entry is always the reserved
         * {@code datadog.local_root_span_id} slot; user-registered keys follow
         * in registration order.
         */
        public final String[] attributeKeyMap;

        public ProcessContext(String deploymentEnvironmentName, String hostName, String serviceInstanceId, String serviceName, String serviceVersion, String telemetrySdkLanguage, String telemetrySdkVersion, String telemetrySdkName, String[] attributeKeyMap) {
            this.deploymentEnvironmentName = deploymentEnvironmentName;
            this.hostName = hostName;
            this.serviceInstanceId = serviceInstanceId;
            this.serviceName = serviceName;
            this.serviceVersion = serviceVersion;
            this.telemetrySdkLanguage = telemetrySdkLanguage;
            this.telemetrySdkVersion = telemetrySdkVersion;
            this.telemetrySdkName = telemetrySdkName;
            this.attributeKeyMap = attributeKeyMap;
        }

        @Override
        public String toString() {
            return String.format("ProcessContext{deploymentEnvironmentName='%s', hostName='%s', serviceInstanceId='%s', serviceName='%s', serviceVersion='%s', telemetrySdkLanguage='%s', telemetrySdkVersion='%s', telemetrySdkName='%s', attributeKeyMap=%s}",
                deploymentEnvironmentName, hostName, serviceInstanceId, serviceName, serviceVersion, telemetrySdkLanguage, telemetrySdkVersion, telemetrySdkName, java.util.Arrays.toString(attributeKeyMap));
        }
    }
    
    /**
     * Returns the singleton instance of the OpenTelemetry process context.
     * 
     * <p>This method provides access to the globally shared OTelContext instance
     * using the lazy initialization pattern. The instance is created on first access
     * and reused for all subsequent calls.
     * 
     * <p><b>Note:</b> If library loading fails during initialization, a warning
     * will be printed to System.out, but a valid (though non-functional) instance
     * will still be returned.
     *
     * @return the singleton OTelContext instance, never null
     */
    public static OTelContext getInstance() {
        return SingletonHolder.INSTANCE;
    }

    private final LibraryLoader.Result libraryLoadResult;
    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

    /**
     * Private constructor for singleton instance.
     * 
     * <p>Initializes the native library and handles any loading failures gracefully
     * by printing warnings to System.out.
     */
    private OTelContext() {
        LibraryLoader.Result result = LibraryLoader.builder().library(LibraryLoader.Library.SUPPORT).load();
        if (!result.succeeded ) {
            System.out.println("[WARNING] Failed to obtain OTel context.\n" + result.error);
        }
        libraryLoadResult = result;
    }

    /**
     * Creates a custom OTelContext instance with specific library loading configuration.
     * 
     * <p>This constructor allows for advanced configuration of the native library loading
     * process, including custom library locations and error handling. Most users should
     * use {@link #getInstance()} instead.
     * 
     * <p><b>Warning:</b> Creating multiple instances may lead to undefined behavior
     * as the underlying native library maintains global state.
     * 
     * @param libLocation the custom library location, or null to use default discovery
     * @param scratchDir the scratch directory for temporary files, or null for system default
     * @param errorHandler custom error handler for library loading failures, or null 
     *                     to print warnings to System.out
     */
    public OTelContext(String libLocation, String scratchDir, Consumer<Throwable> errorHandler) {
        LibraryLoader.Result result = LibraryLoader.builder().library(LibraryLoader.Library.SUPPORT).withLibraryLocation(libLocation).withScratchDir(scratchDir).load();
        if (!result.succeeded && result.error != null) {
            if (errorHandler != null) {
                errorHandler.accept(result.error);
            } else {
                System.out.println("[WARNING] Failed to obtain OTelContext access.\n" + result.error);
            }
        }
        libraryLoadResult = result;
    }

    /**
     * Reads the currently published OpenTelemetry process context, if any.
     * 
     * <p>This method attempts to read back the process context that was previously
     * published via {@link #initializeAllContext(String, String, String, String, String, String, String[])}. This is
     * primarily useful for debugging and testing purposes.
     * 
     * <p><b>Platform Support:</b> Currently only supported on Linux. On other
     * platforms, this method will return null.
     *
     * @return a ProcessContext object containing the current context data if
     *         successfully read, or null if no context is published or reading failed
     * @since 1.30.0
     */
    public ProcessContext readProcessContext() {
        if (!libraryLoadResult.succeeded) {
            return null;
        }
        try {
            lock.readLock().lock();
            return readProcessCtx0();
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Initializes the OpenTelemetry context shared with external profilers: it publishes the
     * process-level context and, as part of the same call, sets up the custom thread-context
     * attribute names ({@code attributeKeys}) as the {@code attribute_key_map}. Callers must
     * invoke this method for those custom attribute names to be published.
     *
     * <p><b>Important:</b> if this method is mistakenly not called, the omission is easy to miss
     * because nothing visibly breaks; java-profiler keeps working and in-process profiling and
     * per-thread context capture are unaffected. The only effect is silent and external: readers
     * implementing the OpenTelemetry context sharing specification will be unable to read
     * this information (the process context and the thread-context {@code attribute_key_map}).
     * 
     * <p>This method publishes process-level context information following OpenTelemetry
     * semantic conventions. The context is made available to external monitoring tools
     * and profilers through platform-specific mechanisms.
     * 
     * <p><b>On Linux:</b> Creates a named anonymous memory mapping that can be
     * discovered by external tools scanning /proc/&#42;/maps for &#91;anon:OTEL_CTX&#93;
     * entries.
     * 
     * <p><b>On other platforms:</b> This method is a no-op as process context
     * sharing is not currently supported.
     * 
     * <p><b>Context Lifecycle:</b> The published context remains active until
     * the process exits. Calling this method multiple times will replace the previous
     * context with the new values.
     * 
     * <p><b>Usage Example:</b>
     * <pre>{@code
     * OTelContext.getInstance().initializeAllContext(
     *     "staging",           // env
     *     "my-hostname",       // hostname
     *     "instance-12345",    // runtime-id
     *     "my-service",        // service
     *     "1.0.0",             // version
     *     "3.5.0",             // tracer-version
     *     new String[] {"http.route", "db.system"}  // thread-context attribute keys
     * );
     * }</pre>
     *
     * @param env the deployment environment name as defined by OpenTelemetry
     *            semantic conventions (deployment.environment.name). Must not be null.
     *            Examples: "production", "staging", "development", "test"
     * @param hostname the hostname of the service, recorded under the OpenTelemetry
     *                 semantic convention key host.name as a resource attribute. Must not be null.
     *                 Examples: "my-hostname", "my-hostname.example.com"
     * @param runtimeId the unique identifier for this specific instance of the service
     *                  as defined by OpenTelemetry semantic conventions (service.instance.id).
     *                  Must not be null.
     * @param service the logical name of the service as defined by OpenTelemetry
     *                semantic conventions (service.name). Must not be null.
     *                Examples: "order-service", "user-management", "payment-processor"
     * @param version the version of the service as defined by OpenTelemetry
     *                semantic conventions (service.version). Must not be null.
     *                Examples: "1.0.0", "2.3.4"
     * @param tracerVersion the version of the tracer as defined by OpenTelemetry
     *                      semantic conventions (telemetry.sdk.version). Must not be null.
     *                      Examples: "3.5.0", "4.2.0"
     * @param attributeKeys the thread-context attribute key names whose per-thread
     *                      values are recorded in the OTEP thread-local record (e.g.
     *                      "http.route", "db.system"). Published in the process context's
     *                      thread_ctx_config as the attribute_key_map, preceded by the
     *                      reserved datadog.local_root_span_id slot. Must not be null
     *                      (may be empty); keys beyond capacity are clipped. If any
     *                      element is null, the entire process context publish is
     *                      skipped - no context is published (a warning is logged) and
     *                      no exception is thrown. Order must match the indices used
     *                      with {@link ThreadContext#setContextAttribute(int, String)}.
     *
     * @throws NullPointerException if {@code attributeKeys} is null
     *
     * @see <a href="https://opentelemetry.io/docs/specs/semconv/registry/attributes/service/">OpenTelemetry Service Attributes</a>
     * @see <a href="https://opentelemetry.io/docs/specs/semconv/registry/attributes/deployment/">OpenTelemetry Deployment Attributes</a>
     */
    /** @deprecated Use {@link #initializeAllContext(String, String, String, String, String, String, String[])} instead. */
    @Deprecated
    public void setProcessContext(String env, String hostname, String runtimeId, String service, String version, String tracerVersion) {
        initializeAllContext(env, hostname, runtimeId, service, version, tracerVersion, new String[0]);
    }

    public void initializeAllContext(String env, String hostname, String runtimeId, String service, String version, String tracerVersion, String[] attributeKeys) {
        Objects.requireNonNull(attributeKeys, "attributeKeys");
        if (!libraryLoadResult.succeeded) {
            return;
        }
        try {
            lock.writeLock().lock();
            setProcessCtx0(env, hostname, runtimeId, service, version, tracerVersion, attributeKeys);
        } finally {
            lock.writeLock().unlock();
        }
    }

    private static native void setProcessCtx0(String env, String hostname, String runtimeId, String service, String version, String tracerVersion, String[] attributeKeys);
    private static native ProcessContext readProcessCtx0();
}
