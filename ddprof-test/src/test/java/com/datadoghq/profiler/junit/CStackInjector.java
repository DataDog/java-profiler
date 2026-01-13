package com.datadoghq.profiler.junit;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestInfo;
import org.junit.jupiter.api.extension.Extension;
import org.junit.jupiter.api.extension.ExtensionContext;
import org.junit.jupiter.api.extension.InvocationInterceptor;
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
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;
import java.util.stream.Stream;

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
        if (Platform.isZing()) {
            // zing is a bit iffy when using anything but 'no' for cstack
            return Stream.of(new ParameterizedTestContext("no", retryCount));
        } else {
            return Stream.of(valueSource.strings()).
                    filter(CStackInjector::isModeSafe).
                    map(param -> new ParameterizedTestContext(param, retryCount));
        }
    }

    private static boolean isModeSafe(String mode) {
        if (Platform.isJ9()) {
            return "dwarf".equals(mode);
        }
        if (Platform.isAarch64() && !Platform.isJavaVersionAtLeast(17)) {
            return mode.startsWith("vm");
        }
        if (AbstractProfilerTest.isInCI()) {
            if (Platform.isMusl() && !Platform.isAarch64()) {
                // our CI runner for musl on x64 is iffy and inexplicably locks up
                //   randomly when doing vm stackwalking
                return !mode.startsWith("vm");
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

        ParameterizedTestContext(String parameter, int retryCount) {
            this.parameter = parameter;
            this.retryCount = retryCount;
        }

        @Override
        public String getDisplayName(int invocationIndex) {
            return "cstack=" + parameter;
        }

        @Override
        public List<Extension> getAdditionalExtensions() {
            List<Extension> extensions = new ArrayList<>(TestTemplateInvocationContext.super.getAdditionalExtensions());
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
                                testMethod.invoke(testInstance, parameter);
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
