---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 09:14:00 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 27-48 cores)</summary>

```
1786367399 27
1786367404 40
1786367409 40
1786367414 40
1786367419 40
1786367424 40
1786367429 40
1786367434 40
1786367439 40
1786367444 40
1786367449 40
1786367454 40
1786367459 48
1786367464 48
1786367469 48
1786367474 48
1786367479 48
1786367484 48
1786367489 48
1786367494 48
```
</details>

---

