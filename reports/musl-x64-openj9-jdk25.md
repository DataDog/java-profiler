---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-27 13:40:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 18.00/sec |
| Health Score | 1125% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 26.67/sec |
| Health Score | 1667% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1769538864 32
1769538869 32
1769538874 32
1769538879 32
1769538884 32
1769538889 32
1769538894 32
1769538899 32
1769538904 32
1769538909 32
1769538914 32
1769538919 32
1769538924 32
1769538929 32
1769538934 32
1769538939 32
1769538944 32
1769538949 32
1769538954 32
1769538959 32
```
</details>

---

