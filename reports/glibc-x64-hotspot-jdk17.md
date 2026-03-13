---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:26:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1773393629 56
1773393634 56
1773393639 56
1773393644 56
1773393649 56
1773393654 60
1773393659 60
1773393664 60
1773393669 60
1773393674 58
1773393679 58
1773393684 58
1773393689 58
1773393694 58
1773393699 58
1773393704 58
1773393709 58
1773393714 58
1773393719 58
1773393724 58
```
</details>

---

