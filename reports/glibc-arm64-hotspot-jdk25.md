---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 09:47:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1791466859 48
1791466864 48
1791466869 48
1791466874 48
1791466879 48
1791466884 48
1791466889 48
1791466894 46
1791466899 46
1791466904 46
1791466909 46
1791466914 46
1791466919 46
1791466924 46
1791466929 46
1791466934 37
1791466939 37
1791466944 37
1791466949 37
1791466954 37
```
</details>

---

