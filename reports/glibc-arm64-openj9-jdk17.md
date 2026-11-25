---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:51:47 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 12 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 29-60 cores)</summary>

```
1795632447 29
1795632453 29
1795632458 29
1795632463 29
1795632468 29
1795632473 29
1795632478 29
1795632483 29
1795632488 29
1795632493 29
1795632498 29
1795632503 29
1795632508 29
1795632513 60
1795632518 60
1795632523 60
1795632528 60
1795632533 60
1795632538 60
1795632543 60
```
</details>

---

