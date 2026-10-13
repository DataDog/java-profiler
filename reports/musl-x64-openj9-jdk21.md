---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 13:24:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 42-64 cores)</summary>

```
1791911834 42
1791911839 42
1791911844 42
1791911849 42
1791911854 42
1791911859 42
1791911864 42
1791911869 42
1791911874 42
1791911879 42
1791911884 64
1791911889 64
1791911894 64
1791911899 64
1791911904 64
1791911909 64
1791911914 64
1791911919 64
1791911924 64
1791911929 64
```
</details>

---

