package com.datadoghq.profiler;

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
 *   <li><b>macOS:</b> Limited support - API calls are no-ops</li>
 *   <li><b>Other platforms:</b> Not supported</li>
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
 * context.setProcessContext(
 *     "my-service",           // service name
 *     "instance-12345",       // unique instance identifier  
 *     "production"            // deployment environment
 * );
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

    /**
     * Private constructor for singleton instance.
     * 
     * <p>Initializes the native library and handles any loading failures gracefully
     * by printing warnings to System.out.
     */
    private OTelContext() {
        LibraryLoader.Result result = LibraryLoader.builder().load();
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
    // @VisibleForTesting
    OTelContext(String libLocation, String scratchDir, Consumer<Throwable> errorHandler) {
        LibraryLoader.Result result = LibraryLoader.builder().withLibraryLocation(libLocation).withScratchDir(scratchDir).load();
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
     * published via {@link #setProcessContext(String, String, String)}. This is
     * primarily useful for debugging and testing purposes.
     * 
     * <p><b>Platform Support:</b> Currently only supported on Linux. On other
     * platforms, this method will return null.
     * 
     * <p><b>Thread Safety:</b> This method assumes there is no concurrent mutation
     * of the process context and is safe to call from any thread.
     * 
     * @return a ProcessContext object containing the current context data if
     *         successfully read, or null if no context is published or reading failed
     * @since 1.30.0
     */
    public ProcessContext readProcessContext() {
        return readProcessCtx0();
    }

    /**
     * Represents the OpenTelemetry process context data.
     */
    public static final class ProcessContext {
        public final String serviceName;
        public final String serviceInstanceId;
        public final String deploymentEnvironmentName;
        
        public ProcessContext(String serviceName, String serviceInstanceId, String deploymentEnvironmentName) {
            this.serviceName = serviceName;
            this.serviceInstanceId = serviceInstanceId;
            this.deploymentEnvironmentName = deploymentEnvironmentName;
        }
        
        @Override
        public String toString() {
            return String.format("ProcessContext{serviceName='%s', serviceInstanceId='%s', deploymentEnvironmentName='%s'}", 
                serviceName, serviceInstanceId, deploymentEnvironmentName);
        }
    }

    /**
     * Sets the OpenTelemetry process context for external discovery and monitoring.
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
     * OTelContext.getInstance().setProcessContext(
     *     "order-service",        // Identifies the service
     *     "pod-abc123",          // Unique instance ID (e.g., pod name, container ID)
     *     "production"           // Environment (production, staging, dev, etc.)
     * );
     * }</pre>
     * 
     * @param service the logical name of the service as defined by OpenTelemetry
     *                semantic conventions (service.name). Must not be null.
     *                Examples: "order-service", "user-management", "payment-processor"
     * @param runtimeId the unique identifier for this specific instance of the service
     *                  as defined by OpenTelemetry semantic conventions (service.instance.id).
     *                  Must not be null. Examples: pod name, container ID, hostname
     * @param environment the deployment environment name as defined by OpenTelemetry
     *                   semantic conventions (deployment.environment.name). Must not be null.
     *                   Examples: "production", "staging", "development", "test"
     *                   
     * @throws RuntimeException if the native library failed to load during initialization
     * 
     * @see <a href="https://opentelemetry.io/docs/specs/semconv/registry/attributes/service/">OpenTelemetry Service Attributes</a>
     * @see <a href="https://opentelemetry.io/docs/specs/semconv/registry/attributes/deployment/">OpenTelemetry Deployment Attributes</a>
     */
    public void setProcessContext(String service, String runtimeId, String environment) {
        setProcessCtx0(service, runtimeId, environment);
    }

    private static native void setProcessCtx0(String serviceName, String serviceId, String environment);
    private static native ProcessContext readProcessCtx0();
}