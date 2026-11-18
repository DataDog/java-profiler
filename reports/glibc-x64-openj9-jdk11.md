---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:33:14 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 41-60 cores)</summary>

```
1795015589 43
1795015594 43
1795015599 43
1795015604 43
1795015609 41
1795015614 41
1795015619 41
1795015624 41
1795015629 41
1795015634 41
1795015639 43
1795015644 43
1795015649 43
1795015654 43
1795015659 43
1795015664 43
1795015669 43
1795015674 43
1795015679 43
1795015684 43
```
</details>

---

