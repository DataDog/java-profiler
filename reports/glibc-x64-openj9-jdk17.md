---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:28:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 18-28 cores)</summary>

```
1772734966 18
1772734971 18
1772734976 18
1772734981 28
1772734986 28
1772734991 28
1772734996 28
1772735001 28
1772735006 28
1772735011 28
1772735016 28
1772735021 28
1772735026 28
1772735031 28
1772735036 28
1772735041 28
1772735046 28
1772735051 28
1772735056 28
1772735061 28
```
</details>

---

