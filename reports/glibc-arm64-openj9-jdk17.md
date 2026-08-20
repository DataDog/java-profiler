---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 10:46:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1787236956 64
1787236961 64
1787236966 64
1787236971 64
1787236976 64
1787236981 62
1787236986 62
1787236991 62
1787236996 62
1787237001 62
1787237006 62
1787237011 62
1787237016 62
1787237021 62
1787237026 62
1787237031 62
1787237036 62
1787237041 62
1787237046 62
1787237051 62
```
</details>

---

