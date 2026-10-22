---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:39:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 85-94 cores)</summary>

```
1792686770 94
1792686775 94
1792686780 94
1792686785 94
1792686790 86
1792686795 86
1792686800 86
1792686805 86
1792686810 86
1792686815 86
1792686820 86
1792686825 86
1792686830 86
1792686835 86
1792686840 86
1792686845 86
1792686850 86
1792686855 86
1792686860 86
1792686865 88
```
</details>

---

