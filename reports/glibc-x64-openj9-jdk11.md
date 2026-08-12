---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 04:18:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 28-40 cores)</summary>

```
1786522408 28
1786522413 40
1786522418 40
1786522423 40
1786522428 40
1786522433 40
1786522438 40
1786522443 40
1786522448 40
1786522453 40
1786522458 40
1786522463 40
1786522468 40
1786522473 40
1786522478 40
1786522483 40
1786522488 40
1786522493 40
1786522498 40
1786522503 40
```
</details>

---

