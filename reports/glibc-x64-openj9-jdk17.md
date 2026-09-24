---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 05:28:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 36-46 cores)</summary>

```
1790241549 37
1790241554 37
1790241559 37
1790241564 37
1790241569 46
1790241574 46
1790241579 46
1790241584 46
1790241589 46
1790241594 46
1790241599 46
1790241604 46
1790241609 46
1790241614 46
1790241619 46
1790241624 46
1790241629 46
1790241634 36
1790241639 36
1790241644 36
```
</details>

---

