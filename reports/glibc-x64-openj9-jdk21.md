---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 01:04:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 45-81 cores)</summary>

```
1793336418 45
1793336423 45
1793336428 45
1793336433 45
1793336438 45
1793336443 45
1793336448 45
1793336453 45
1793336458 45
1793336463 45
1793336468 45
1793336473 45
1793336478 45
1793336483 45
1793336488 45
1793336493 45
1793336498 45
1793336503 81
1793336508 81
1793336513 81
```
</details>

---

