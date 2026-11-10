// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.junit;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.lang.reflect.Parameter;
import java.lang.reflect.Proxy;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.api.extension.BeforeEachCallback;
import org.junit.jupiter.api.extension.ConditionEvaluationResult;
import org.junit.jupiter.api.extension.ExecutionCondition;
import org.junit.jupiter.api.extension.ExtendWith;
import org.junit.jupiter.api.extension.Extension;
import org.junit.jupiter.api.extension.ExtensionContext;
import org.junit.jupiter.api.extension.ParameterContext;
import org.junit.jupiter.api.extension.ParameterResolver;
import org.junit.jupiter.api.extension.TestTemplateInvocationContext;
import org.junit.jupiter.api.extension.TestTemplateInvocationContextProvider;
import org.junit.jupiter.params.provider.ValueSource;
import org.junit.platform.engine.discovery.DiscoverySelectors;
import org.junit.platform.launcher.TestExecutionListener;
import org.junit.platform.launcher.TestIdentifier;
import org.junit.platform.launcher.core.LauncherDiscoveryRequestBuilder;
import org.junit.platform.launcher.core.LauncherFactory;
import org.junit.platform.launcher.listeners.SummaryGeneratingListener;
import org.junit.platform.launcher.listeners.TestExecutionSummary;

import static org.junit.jupiter.api.Assertions.*;

/** Checks shared mode policy and real-engine lifecycle ordering without native startup. */
public class CStackInjectorPolicyTest {
    private static final String[] VM_MODES = {"vm", "vmx"};
    private static int setupEntries;
    private static int callbacks;
    private static int before;
    private static int body;
    private static int after;
    private static final List<String> constructed = new ArrayList<>();
    private static final List<String> executed = new ArrayList<>();

    @Test
    void ordinaryHotspotRetainsVmx() throws Exception {
        assertEnabled(select(new String[] {"vmx"}, policy(false, false, true, false, false)), "vmx");
    }

    @Test
    void ordinaryHotspotPreservesOrderAndDuplicates() throws Exception {
        assertEnabled(select(new String[] {"vm", "vmx", "fp", "dwarf", "vm"},
                policy(false, false, true, false, false)), "vm", "vmx", "fp", "dwarf", "vm");
    }

    @Test
    void muslArm64CiRetainsVmFromMixedDeclaration() throws Exception {
        assertEnabled(select(VM_MODES, policy(false, true, true, true, true)), "vm");
    }

    @Test
    void muslArm64CiDisablesVmxOnlyDeclaration() throws Exception {
        assertDisabled(select(new String[] {"vmx"}, policy(false, true, true, true, true)), "vmx");
    }

    @Test
    void muslX64CiDisablesAllVmModes() throws Exception {
        assertDisabled(select(VM_MODES, policy(false, false, true, true, true)), "vm");
    }

    @Test
    void muslX64CiRetainsDwarf() throws Exception {
        assertEnabled(select(new String[] {"vm", "dwarf"}, policy(false, false, true, true, true)), "dwarf");
    }

    @Test
    void nonCiMuslRetainsVmModesOnBothArchitectures() throws Exception {
        for (boolean aarch64 : new boolean[] {false, true}) {
            assertEnabled(select(VM_MODES, policy(false, aarch64, true, false, true)), "vm", "vmx");
        }
    }

    @Test
    void glibcCiRetainsVmModesOnBothArchitectures() throws Exception {
        for (boolean aarch64 : new boolean[] {false, true}) {
            assertEnabled(select(VM_MODES, policy(false, aarch64, true, true, false)), "vm", "vmx");
        }
    }

    @Test
    void j9DisablesAllVmModes() throws Exception {
        assertDisabled(select(VM_MODES, policy(true, false, true, false, false)), "vm");
    }

    @Test
    void j9RetainsOnlyDwarf() throws Exception {
        assertEnabled(select(new String[] {"vm", "dwarf"}, policy(true, false, true, false, false)), "dwarf");
    }

    @Test
    void pre17Arm64PolicyPrecedesCiMuslExclusion() throws Exception {
        assertEnabled(select(new String[] {"fp", "dwarf", "vm", "vmx"},
                policy(false, true, false, true, true)), "vm", "vmx");
    }

    @Test
    void earlyPolicyBranchesDoNotProbeLibc() {
        assertTrue(CStackInjector.isModeSafe("dwarf", true, true, false, true, () -> {
            throw new AssertionError("J9 must return before libc detection");
        }));
        assertTrue(CStackInjector.isModeSafe("vmx", false, true, false, true, () -> {
            throw new AssertionError("Pre-17 ARM64 must return before libc detection");
        }));
        assertTrue(CStackInjector.isModeSafe("vmx", false, false, true, false, () -> {
            throw new AssertionError("Non-CI must not detect libc");
        }));
    }

    @Test
    void zingUsesNoWithoutConsultingModePredicate() throws Exception {
        assertEnabled(CStackInjector.selectContexts(VM_MODES, 0, true, mode -> {
            throw new AssertionError("Zing must bypass the safety predicate");
        }).collect(Collectors.toList()), "no");
    }

    @Test
    void disabledInvocationSkipsInheritedProfilerSetupAndAllPerTestLifecycle() {
        resetLifecycle();
        List<String> reasons = new ArrayList<>();
        TestExecutionSummary summary = launch(ExcludedFixture.class, reasons);
        assertEquals(1, summary.getTestsFoundCount());
        assertEquals(1, summary.getTestsSkippedCount());
        assertEquals(0, summary.getTestsStartedCount());
        assertEquals(0, summary.getTestsSucceededCount());
        assertEquals(0, summary.getTestsAbortedCount());
        assertEquals(0, summary.getTestsFailedCount());
        assertEquals(0, summary.getContainersFailedCount());
        assertTrue(summary.getFailures().isEmpty());
        assertEquals(1, reasons.size());
        assertFalse(reasons.get(0).trim().isEmpty());
        assertTrue(reasons.get(0).contains("No declared cstack mode is safe"));
        assertEquals(Arrays.asList("vmx"), constructed);
        assertEquals(0, setupEntries);
        assertEquals(0, callbacks);
        assertEquals(0, before);
        assertEquals(0, body);
        assertEquals(0, after);
        assertTrue(executed.isEmpty());
    }

    @Test
    void safeSelectionExecutesCompleteLifecycle() {
        assertEnabledLifecycle(EnabledFixture.class, "vm");
    }

    @Test
    void zingNoExecutesCompleteLifecycle() {
        assertEnabledLifecycle(ZingFixture.class, "no");
    }

    private static Predicate<String> policy(boolean j9, boolean arm64, boolean java17, boolean ci, boolean musl) {
        return mode -> CStackInjector.isModeSafe(mode, j9, arm64, java17, ci, () -> musl);
    }

    private static List<TestTemplateInvocationContext> select(String[] modes, Predicate<String> safe) {
        return CStackInjector.selectContexts(modes, 0, false, safe).collect(Collectors.toList());
    }

    private static void assertEnabled(List<TestTemplateInvocationContext> contexts, String... expected) throws Exception {
        assertEquals(expected.length, contexts.size());
        for (int i = 0; i < expected.length; i++) {
            TestTemplateInvocationContext context = contexts.get(i);
            assertEquals("cstack=" + expected[i], context.getDisplayName(i + 1));
            assertResolvedParameters(context, expected[i]);
            for (Extension extension : context.getAdditionalExtensions()) {
                if (extension instanceof ExecutionCondition) {
                    assertFalse(((ExecutionCondition) extension).evaluateExecutionCondition(null).isDisabled());
                }
            }
        }
    }

    private static void assertDisabled(List<TestTemplateInvocationContext> contexts, String injected) throws Exception {
        assertEquals(1, contexts.size());
        TestTemplateInvocationContext context = contexts.get(0);
        assertTrue(context.getDisplayName(1).contains("disabled"));
        assertResolvedParameters(context, injected);
        List<ExecutionCondition> conditions = context.getAdditionalExtensions().stream()
                .filter(ExecutionCondition.class::isInstance).map(ExecutionCondition.class::cast).collect(Collectors.toList());
        assertEquals(1, conditions.size());
        ConditionEvaluationResult result = conditions.get(0).evaluateExecutionCondition(null);
        assertTrue(result.isDisabled());
        assertTrue(result.getReason().isPresent());
        assertFalse(result.getReason().get().trim().isEmpty());
        assertTrue(result.getReason().get().contains("No declared cstack mode is safe"));
    }

    private static void assertResolvedParameters(TestTemplateInvocationContext context, String expected) throws Exception {
        List<ParameterResolver> resolvers = context.getAdditionalExtensions().stream()
                .filter(ParameterResolver.class::isInstance).map(ParameterResolver.class::cast).collect(Collectors.toList());
        assertEquals(1, resolvers.size());
        Parameter constructor = ExcludedFixture.class.getDeclaredConstructor(String.class).getParameters()[0];
        Parameter[] method = CStackInjectorPolicyTest.class.getDeclaredMethod("parameters", String.class, String.class, int.class).getParameters();
        for (Parameter parameter : new Parameter[] {constructor, method[0]}) {
            ParameterContext parameterContext = parameterContext(parameter);
            assertTrue(resolvers.get(0).supportsParameter(parameterContext, null));
            assertEquals(expected, resolvers.get(0).resolveParameter(parameterContext, null));
        }
        assertFalse(resolvers.get(0).supportsParameter(parameterContext(method[1]), null));
        assertFalse(resolvers.get(0).supportsParameter(parameterContext(method[2]), null));
    }

    private static ParameterContext parameterContext(Parameter parameter) {
        return (ParameterContext) Proxy.newProxyInstance(ParameterContext.class.getClassLoader(),
                new Class<?>[] {ParameterContext.class}, (proxy, method, args) -> {
                    if (method.getName().equals("getParameter")) return parameter;
                    throw new AssertionError("Unexpected ParameterContext access: " + method.getName());
                });
    }

    private void parameters(@CStack String mode, String unannotated, @CStack int wrongType) {}

    private static void resetLifecycle() {
        setupEntries = callbacks = before = body = after = 0;
        constructed.clear();
        executed.clear();
    }

    private static TestExecutionSummary launch(Class<?> fixture, List<String> reasons) {
        SummaryGeneratingListener summary = new SummaryGeneratingListener();
        LauncherFactory.create().execute(LauncherDiscoveryRequestBuilder.request()
                        .selectors(DiscoverySelectors.selectClass(fixture)).build(), summary,
                new TestExecutionListener() {
                    @Override
                    public void executionSkipped(TestIdentifier test, String reason) {
                        if (test.isTest()) reasons.add(reason);
                    }
                });
        return summary.getSummary();
    }

    private static void assertEnabledLifecycle(Class<?> fixture, String mode) {
        resetLifecycle();
        List<String> reasons = new ArrayList<>();
        TestExecutionSummary summary = launch(fixture, reasons);
        assertEquals(1, summary.getTestsFoundCount());
        assertEquals(1, summary.getTestsStartedCount());
        assertEquals(1, summary.getTestsSucceededCount());
        assertEquals(0, summary.getTestsSkippedCount());
        assertEquals(0, summary.getTestsAbortedCount());
        assertEquals(0, summary.getTestsFailedCount());
        assertEquals(0, summary.getContainersFailedCount());
        assertTrue(summary.getFailures().isEmpty());
        assertTrue(reasons.isEmpty());
        assertEquals(Arrays.asList(mode), executed);
        assertEquals(1, callbacks);
        assertEquals(1, before);
        assertEquals(1, body);
        assertEquals(1, after);
    }

    /** Uses the real inherited setup, but aborts before JNI if the exclusion regresses. */
    @ExtendWith({MuslArm64CiProvider.class, LifecycleCallback.class})
    public static class ExcludedFixture extends AbstractProfilerTest {
        public ExcludedFixture(@CStack String mode) {
            super(mapOf("cstack", mode));
            constructed.add(mode);
        }

        @Override
        protected boolean isPlatformSupported() {
            setupEntries++;
            return false;
        }

        @Override
        protected String getProfilerCommand() {
            throw new AssertionError("Excluded setup must stop before constructing a command");
        }

        @BeforeEach
        void beforeInvocation() { before++; }

        @AfterEach
        void afterInvocation() { after++; }

        @TestTemplate
        @ValueSource(strings = {"vmx"})
        void workload(@CStack String mode) {
            body++;
            executed.add(mode);
        }
    }

    /** No-JNI control for retained mode lifecycle and method parameter resolution. */
    @ExtendWith({MuslArm64CiProvider.class, LifecycleCallback.class})
    public static class EnabledFixture {
        @BeforeEach
        void beforeInvocation() { before++; }

        @AfterEach
        void afterInvocation() { after++; }

        @TestTemplate
        @ValueSource(strings = {"vm", "vmx"})
        void workload(@CStack String mode) {
            body++;
            executed.add(mode);
        }
    }

    /** Keeps the Zing provider isolated from the ordinary-policy fixture. */
    @ExtendWith({ZingProvider.class, LifecycleCallback.class})
    public static class ZingFixture {
        @BeforeEach
        void beforeInvocation() { before++; }

        @AfterEach
        void afterInvocation() { after++; }

        @TestTemplate
        @ValueSource(strings = {"vm", "vmx"})
        void workload(@CStack String mode) {
            body++;
            executed.add(mode);
        }
    }

    /** Detects any entry into per-invocation callbacks before setup. */
    public static class LifecycleCallback implements BeforeEachCallback {
        @Override
        public void beforeEach(ExtensionContext context) { callbacks++; }
    }

    /** Supplies the existing musl ARM64 CI policy without changing host properties. */
    public static class MuslArm64CiProvider extends SyntheticProvider {
        public MuslArm64CiProvider() { super(false); }
    }

    /** Selects the separate Zing branch under the same synthetic policy. */
    public static class ZingProvider extends SyntheticProvider {
        public ZingProvider() { super(true); }
    }

    /** Runs shared production selection with synthetic musl ARM64 CI facts. */
    public abstract static class SyntheticProvider implements TestTemplateInvocationContextProvider {
        private final boolean zing;

        SyntheticProvider(boolean zing) { this.zing = zing; }

        @Override
        public boolean supportsTestTemplate(ExtensionContext context) {
            return new CStackInjector().supportsTestTemplate(context);
        }

        @Override
        public Stream<TestTemplateInvocationContext> provideTestTemplateInvocationContexts(ExtensionContext context) {
            return CStackInjector.selectContexts(context.getRequiredTestMethod().getAnnotation(ValueSource.class).strings(),
                    0, zing, policy(false, true, true, true, true));
        }
    }
}
