---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 09:03:27 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 68-75 cores)</summary>

```
1795442315 68
1795442320 68
1795442325 68
1795442330 68
1795442335 68
1795442340 68
1795442345 68
1795442350 68
1795442355 73
1795442360 73
1795442365 73
1795442370 71
1795442375 71
1795442380 73
1795442385 73
1795442390 73
1795442395 73
1795442400 73
1795442405 73
1795442410 73
```
</details>

---

