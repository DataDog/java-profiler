package com.datadoghq.profiler.test;

import org.junit.platform.engine.discovery.ClassNameFilter;
import org.junit.platform.engine.discovery.DiscoverySelectors;
import org.junit.platform.launcher.Launcher;
import org.junit.platform.launcher.LauncherDiscoveryRequest;
import org.junit.platform.launcher.core.LauncherDiscoveryRequestBuilder;
import org.junit.platform.launcher.core.LauncherFactory;
import org.junit.platform.launcher.listeners.SummaryGeneratingListener;

import java.io.PrintWriter;

/**
 * Custom test runner using JUnit Platform Launcher API.
 *
 * This runner bypasses JUnit Platform Console Launcher, avoiding known issues with:
 * - Assertion handling differences
 * - JVM argument forwarding
 * - Classpath mounting problems
 * - NoSuchMethodError on musl + JDK 11
 *
 * Uses the same Launcher API that Gradle's Test task and IDEs use internally,
 * ensuring consistent test execution across all platforms.
 *
 * Test Filtering:
 * - -Dtest.filter=ClassName         - Run all tests in a class
 * - -Dtest.filter=ClassName#method  - Run specific test method
 * - -Dtest.filter=*.Pattern*        - Pattern matching on class names
 */
public class ProfilerTestRunner {
    public static void main(String[] args) {
        try {
            runTests(args);
        } catch (Throwable t) {
            System.err.println("FATAL ERROR in ProfilerTestRunner:");
            t.printStackTrace(System.err);
            System.exit(2);
        }
    }

    private static void runTests(String[] args) {
        // Parse test filter from system property
        String testFilter = System.getProperty("test.filter");

        // Build discovery request
        LauncherDiscoveryRequestBuilder requestBuilder = LauncherDiscoveryRequestBuilder.request();

        if (testFilter != null && !testFilter.isEmpty()) {
            // Apply test filter based on format
            // Support both # and . as method separators for consistency with Gradle Test tasks
            if (testFilter.contains("#")) {
                // Method filter with # separator: ClassName#methodName
                String[] parts = testFilter.split("#", 2);
                requestBuilder.selectors(
                    DiscoverySelectors.selectMethod(parts[0], parts[1])
                );
            } else if (testFilter.contains(".") && !testFilter.startsWith("*") && isMethodFilter(testFilter)) {
                // Method filter with . separator: ClassName.methodName
                // Heuristic: if last segment starts with lowercase, it's probably a method name
                int lastDot = testFilter.lastIndexOf('.');
                String className = testFilter.substring(0, lastDot);
                String methodName = testFilter.substring(lastDot + 1);
                requestBuilder.selectors(
                    DiscoverySelectors.selectMethod(className, methodName)
                );
            } else if (testFilter.contains("*")) {
                // Pattern filter: *.ClassName or package.*
                // Scan entire classpath and apply pattern filter
                requestBuilder.selectors(
                    DiscoverySelectors.selectPackage("")
                );
                requestBuilder.filters(
                    ClassNameFilter.includeClassNamePatterns(testFilter)
                );
            } else {
                // Class filter - support both fully qualified and short names
                // JUnit uses regex patterns, not globs:
                // - Fully qualified: com.foo.Bar -> com\.foo\.Bar (escape dots)
                // - Short name: Bar -> .*\.Bar (match any package)
                String classPattern;
                if (testFilter.contains(".")) {
                    // Fully qualified name - escape dots for regex
                    classPattern = testFilter.replace(".", "\\.");
                } else {
                    // Short name - prefix with .* to match any package
                    classPattern = ".*\\." + testFilter;
                }
                requestBuilder.selectors(
                    DiscoverySelectors.selectPackage("")
                );
                requestBuilder.filters(
                    ClassNameFilter.includeClassNamePatterns(classPattern)
                );
            }
        } else {
            // No filter: scan all classes in classpath
            requestBuilder.selectors(
                DiscoverySelectors.selectPackage("")
            );
        }

        LauncherDiscoveryRequest request = requestBuilder.build();

        // Create launcher and register listener
        Launcher launcher = LauncherFactory.create();
        SummaryGeneratingListener listener = new SummaryGeneratingListener();
        launcher.registerTestExecutionListeners(listener);

        // Execute tests
        launcher.execute(request);

        // Print summary to console
        listener.getSummary().printTo(new PrintWriter(System.out));

        // Exit with appropriate code (0 = success, 1 = failures)
        long failures = listener.getSummary().getFailures().size();
        System.exit(failures > 0 ? 1 : 0);
    }

    /**
     * Heuristic to determine if a filter string is a method filter (ClassName.methodName)
     * rather than just a class name.
     *
     * Convention: method names start with lowercase, class names start with uppercase.
     *
     * IMPORTANT: When using the dot-separator for method filtering, you MUST provide a
     * fully qualified class name. JUnit Platform's selectMethod() requires a FQCN.
     *
     * Examples:
     *   - "com.foo.Bar" -> false (class name)
     *   - "com.foo.Bar.testSomething" -> true (method filter, FQCN + lowercase method)
     *   - "com.foo.Bar.InnerClass" -> false (inner class, "InnerClass" starts with uppercase)
     *   - "Bar.testSomething" -> true (but will FAIL - "Bar" is not a FQCN)
     *
     * For short class names with methods, use the # separator instead: "Bar#testSomething"
     * Or provide the FQCN: "com.foo.Bar.testSomething"
     */
    private static boolean isMethodFilter(String filter) {
        int lastDot = filter.lastIndexOf('.');
        if (lastDot < 0 || lastDot >= filter.length() - 1) {
            return false; // No dot or dot is at the end
        }

        String lastSegment = filter.substring(lastDot + 1);
        if (lastSegment.isEmpty()) {
            return false;
        }

        // Method names conventionally start with lowercase
        return Character.isLowerCase(lastSegment.charAt(0));
    }
}
