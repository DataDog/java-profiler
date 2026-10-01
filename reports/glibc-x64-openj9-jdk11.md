---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:23:41 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 881 |
| Sample Rate | 14.68/sec |
| Health Score | 917% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 16-20 cores)</summary>

```
1790853539 20
1790853544 20
1790853549 20
1790853554 20
1790853559 20
1790853564 18
1790853569 18
1790853574 18
1790853579 18
1790853584 18
1790853589 18
1790853594 16
1790853599 16
1790853604 16
1790853609 16
1790853614 16
1790853619 16
1790853624 16
1790853629 16
1790853634 16
```
</details>

---

