---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:47:30 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1795531369 14
1795531374 14
1795531379 14
1795531384 14
1795531389 14
1795531394 14
1795531399 14
1795531404 14
1795531409 14
1795531414 14
1795531419 14
1795531424 14
1795531429 14
1795531434 14
1795531439 14
1795531444 14
1795531449 14
1795531454 14
1795531459 14
1795531464 14
```
</details>

---

