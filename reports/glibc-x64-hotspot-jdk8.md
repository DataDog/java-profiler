---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-27 07:00:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793098448 30
1793098453 30
1793098458 30
1793098463 30
1793098468 30
1793098473 30
1793098478 30
1793098483 30
1793098488 30
1793098493 30
1793098498 30
1793098503 30
1793098508 30
1793098513 30
1793098518 30
1793098523 30
1793098528 30
1793098533 30
1793098538 30
1793098543 30
```
</details>

---

