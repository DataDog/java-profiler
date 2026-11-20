---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:41:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 59-78 cores)</summary>

```
1795199762 59
1795199767 59
1795199772 59
1795199777 59
1795199782 59
1795199787 59
1795199792 76
1795199797 76
1795199802 78
1795199807 78
1795199812 78
1795199817 78
1795199822 78
1795199827 78
1795199832 78
1795199837 78
1795199842 76
1795199847 76
1795199852 76
1795199857 76
```
</details>

---

