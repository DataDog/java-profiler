---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 05:52:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1054 |
| Sample Rate | 17.57/sec |
| Health Score | 1098% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 37-51 cores)</summary>

```
1791193593 37
1791193598 37
1791193603 39
1791193609 39
1791193614 39
1791193619 39
1791193624 39
1791193629 39
1791193634 39
1791193639 39
1791193644 39
1791193649 39
1791193654 39
1791193659 51
1791193664 51
1791193669 51
1791193674 51
1791193679 51
1791193684 51
1791193689 51
```
</details>

---

