---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:20:50 EST

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795641345 64
1795641350 64
1795641355 64
1795641360 64
1795641365 64
1795641370 47
1795641375 47
1795641380 47
1795641385 47
1795641390 47
1795641395 47
1795641400 47
1795641405 47
1795641411 47
1795641416 47
1795641421 47
1795641426 47
1795641431 47
1795641436 47
1795641441 47
```
</details>

---

