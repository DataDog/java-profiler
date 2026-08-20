---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 10:46:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787236941 96
1787236946 96
1787236951 96
1787236956 96
1787236961 96
1787236966 96
1787236971 96
1787236976 96
1787236981 96
1787236986 96
1787236991 96
1787236996 96
1787237001 94
1787237006 94
1787237011 94
1787237016 94
1787237021 94
1787237026 94
1787237031 96
1787237036 96
```
</details>

---

