# generate-hidden-classes-in-the-lookup-packag

## Finding

`HiddenClassChurnAntagonist.generateClass()` set `internalName = "chaos/hidden/Gen" + uid`,
placing the generated class in package `chaos.hidden`. The lookup object obtained from
`MethodHandles.lookup()` inside `HiddenClassChurnAntagonist` belongs to package
`com.datadoghq.profiler.chaos`. On Java 15+, `Lookup.defineHiddenClass` requires the
bytecode to declare the same package as the lookup class; a mismatch throws
`IllegalArgumentException`, which was silently swallowed by `catch (Throwable t)`. As a
result the antagonist looped without ever defining a hidden class.

## Fix

Change `internalName` to `"com/datadoghq/profiler/chaos/Gen" + uid` so the generated
class's package matches the lookup class.

## File

`ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/HiddenClassChurnAntagonist.java`, line 111
