---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-16 05:46:45 EDT

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
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1786873415 29
1786873420 29
1786873425 29
1786873430 34
1786873435 34
1786873440 34
1786873445 34
1786873450 34
1786873455 34
1786873460 34
1786873465 34
1786873470 34
1786873475 34
1786873480 34
1786873485 34
1786873490 34
1786873495 34
1786873500 34
1786873505 34
1786873510 34
```
</details>

---

