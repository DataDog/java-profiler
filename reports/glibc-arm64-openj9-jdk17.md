---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 17:19:04 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 13 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1786137352 30
1786137357 30
1786137362 30
1786137367 30
1786137372 30
1786137377 30
1786137382 30
1786137387 30
1786137392 30
1786137397 30
1786137402 30
1786137407 30
1786137412 30
1786137417 30
1786137422 30
1786137427 25
1786137432 25
1786137437 25
1786137442 25
1786137447 25
```
</details>

---

