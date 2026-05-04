---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-03 21:21:05 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777857373 59
1777857378 59
1777857383 59
1777857388 59
1777857393 59
1777857398 59
1777857403 59
1777857408 59
1777857413 59
1777857418 64
1777857423 64
1777857428 64
1777857433 64
1777857438 64
1777857443 64
1777857448 64
1777857453 64
1777857458 64
1777857463 64
1777857468 64
```
</details>

---

