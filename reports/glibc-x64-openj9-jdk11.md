---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 03:56:32 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1792655518 62
1792655523 62
1792655528 64
1792655533 64
1792655538 64
1792655543 64
1792655548 64
1792655553 64
1792655558 64
1792655563 64
1792655568 64
1792655573 62
1792655578 62
1792655583 60
1792655588 60
1792655593 60
1792655598 60
1792655603 60
1792655608 62
1792655613 62
```
</details>

---

