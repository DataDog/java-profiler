// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.junit;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestInfo;
import org.junit.jupiter.api.extension.ConditionEvaluationResult;
import org.junit.jupiter.api.extension.ExecutionCondition;
import org.junit.jupiter.api.extension.Extension;
import org.junit.jupiter.api.extension.ExtensionContext;
import org.junit.jupiter.api.extension.ParameterContext;
import org.junit.jupiter.api.extension.ParameterResolutionException;
import org.junit.jupiter.api.extension.ParameterResolver;
import org.junit.jupiter.api.extension.TestExecutionExceptionHandler;
import org.junit.jupiter.api.extension.TestTemplateInvocationContext;
import org.junit.jupiter.api.extension.TestTemplateInvocationContextProvider;
import org.junit.jupiter.params.provider.ValueSource;
import org.opentest4j.TestAbortedException;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.function.BooleanSupplier;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/** Selects platform-safe cstack invocations and supplies their parameters and retry handling. */
public class CStackInjector implements TestTemplateInvocationContextProvider {

    @Override
    public boolean supportsTestTemplate(ExtensionContext context) {
        return context.getTestMethod().isPresent() &&
                context.getTestMethod().get().isAnnotationPresent(ValueSource.class);
    }

    @Override
    public Stream<TestTemplateInvocationContext> provideTestTemplateInvocationContexts(ExtensionContext context) {
        ValueSource valueSource = context.getTestMethod().get().getAnnotation(ValueSource.class);
        // Get retry count from @RetryTest (default = 0)
        int retryCount = context.getTestMethod()
                .flatMap(method -> Optional.ofNullable(method.getAnnotation(RetryTest.class)))
                .map(RetryTest::value)
                .orElse(0);
        return selectContexts(valueSource.strings(), retryCount, Platform.isZing(), CStackInjector::isModeSafe);
    }

    /** Keeps Zing separate from filtering and preserves declared order and duplicates. */
    static Stream<TestTemplateInvocationContext> selectContexts(
            String[] declaredModes, int retryCount, boolean zing, Predicate<String> modeSafe) {
        if (zing) {
            // zing is a bit iffy when using anything but 'no' for cstack
            return Stream.of(new ParameterizedTestContext("no", retryCount));
        } else {
            List<String> safeValues = Stream.of(declaredModes)
                    .filter(modeSafe)
                    .collect(Collectors.toList());
            if (safeValues.isEmpty()) {
                // JUnit requires a context and resolves constructor parameters before skip evaluation.
                // The declared value is injection metadata, not an executable fallback.
                return Stream.of(new ParameterizedTestContext(declaredModes[0], retryCount,
                        "No declared cstack mode is safe on this platform"));
            }
            return safeValues.stream().map(param -> new ParameterizedTestContext(param, retryCount));
        }
    }

    private static boolean isModeSafe(String mode) {
        return isModeSafe(mode, Platform.isJ9(), Platform.isAarch64(),
                Platform.isJavaVersionAtLeast(17), AbstractProfilerTest.isInCI(), Platform::isMusl);
    }

    /** Evaluates the existing exclusions without probing libc on the early-return paths. */
    static boolean isModeSafe(String mode, boolean j9, boolean aarch64,
            boolean java17, boolean ci, BooleanSupplier musl) {
        if (j9) {
            return "dwarf".equals(mode);
        }
        if (aarch64 && !java17) {
            return mode.startsWith("vm");
        }
        if (ci) {
            if (musl.getAsBoolean() && !aarch64) {
                // our CI runner for musl on x64 is iffy and inexplicably locks up
                //   randomly when doing vm stackwalking
                return !mode.startsWith("vm");
            }
            if (musl.getAsBoolean() && aarch64 && "vmx".equals(mode)) {
                // vmx mode has intermittent initialization timing issues on musl aarch64
                // causing 0 events in intermediate JFR dumps
                return false;
            }
        }
        return true;
    }

    public static class TestInfoAdapter implements TestInfo {
        private final String displayName;
        private final Set<String> tags;
        private final Class<?> testClass;
        private final Method testMethod;

        public TestInfoAdapter(String displayName, Set<String> tags, Class<?> testClass, Method testMethod) {
            this.displayName = displayName;
            this.tags = tags;
            this.testClass = testClass;
            this.testMethod = testMethod;
        }

        @Override
        public String getDisplayName() {
            return displayName;
        }

        @Override
        public Set<String> getTags() {
            return tags;
        }

        @Override
        public Optional<Class<?>> getTestClass() {
            return Optional.ofNullable(testClass);
        }

        @Override
        public Optional<Method> getTestMethod() {
            return Optional.ofNullable(testMethod);
        }
    }

    private static class ParameterizedTestContext implements TestTemplateInvocationContext {
        private final String parameter;
        private final int retryCount;
        private final String disabledReason;

        ParameterizedTestContext(String parameter, int retryCount) {
            this(parameter, retryCount, null);
        }

        ParameterizedTestContext(String parameter, int retryCount, String disabledReason) {
            this.parameter = parameter;
            this.retryCount = retryCount;
            this.disabledReason = disabledReason;
        }

        @Override
        public String getDisplayName(int invocationIndex) {
            return "cstack=" + parameter + (disabledReason == null ? "" : " (disabled: no safe mode)");
        }

        @Override
        public List<Extension> getAdditionalExtensions() {
            List<Extension> extensions = new ArrayList<>(TestTemplateInvocationContext.super.getAdditionalExtensions());
            if (disabledReason != null) {
                // Invocation conditions run before BeforeEach callbacks and inherited profiler setup.
                extensions.add((ExecutionCondition) context -> ConditionEvaluationResult.disabled(disabledReason));
            }
            extensions.add(
                    new ParameterResolver() {
                        @Override
                        public boolean supportsParameter(ParameterContext parameterContext, ExtensionContext extensionContext)
                                throws ParameterResolutionException {
                            return parameterContext.getParameter().getType() == String.class && parameterContext.getParameter().isAnnotationPresent(CStack.class);
                        }

                        @Override
                        public Object resolveParameter(ParameterContext parameterContext, ExtensionContext extensionContext)
                                throws ParameterResolutionException {
                            return parameter;
                        }
                    }
            );
            extensions.add(
                    (TestExecutionExceptionHandler) (extensionContext, throwable) -> {
                        // Don't retry on assumption failures - they should skip the test
                        if (throwable instanceof TestAbortedException) {
                            throw throwable;
                        }

                        int attempt = 0;
                        while (++attempt < retryCount) {
                            System.out.println("[Retrying] Attempt " + attempt + "/" + retryCount + " due to failure: " + throwable.getMessage());
                            // Manually reinvoke the test method
                            Method testMethod = extensionContext.getRequiredTestMethod();
                            Object testInstance = extensionContext.getRequiredTestInstance();
                            Class<?> testClass = extensionContext.getRequiredTestClass();
                            String displayName = extensionContext.getDisplayName();
                            TestInfoAdapter testInfo = new TestInfoAdapter(displayName, Collections.emptySet(), testClass, testMethod);

                            List<Method> afterEachMethods = Arrays.stream(testInstance.getClass().getMethods())
                                    .filter(method -> method.isAnnotationPresent(AfterEach.class))
                                    .collect(Collectors.toList());
                            List<Method> beforeEachMethods = Arrays.stream(testInstance.getClass().getMethods())
                                    .filter(method -> method.isAnnotationPresent(BeforeEach.class))
                                    .collect(Collectors.toList());
                            // Retry the test method
                            try {
                                for (Method method : afterEachMethods) {
                                    if (method.getParameterTypes().length == 1 && method.getParameterTypes()[0].isAssignableFrom(TestInfo.class)) {
                                        method.invoke(testInstance, testInfo);
                                    } else {
                                        method.invoke(testInstance);
                                    }
                                }
                                for (Method method : beforeEachMethods) {
                                    if (method.getParameterTypes().length == 1 && method.getParameterTypes()[0].isAssignableFrom(TestInfo.class)) {
                                        method.invoke(testInstance, testInfo);
                                    } else {
                                        method.invoke(testInstance);
                                    }
                                }
                                if (testMethod.getParameterCount() == 0) {
                                    testMethod.invoke(testInstance);
                                } else {
                                    testMethod.invoke(testInstance, parameter);
                                }
                                return; // If the test passes, stop retrying
                            } catch (InvocationTargetException e) {
                                throwable = e.getTargetException();
                            } catch (Throwable t) {
                                throwable = t;
                            }
                        }

                        System.out.println("[Failure] Test failed after " + retryCount + " attempts.");
                        throw throwable;
                    }
            );
            return extensions;
        }

    }
}
