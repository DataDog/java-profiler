---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 09:02:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (4 unique values: 80-86 cores)</summary>

```
1777553845 81
1777553850 81
1777553855 81
1777553860 81
1777553865 81
1777553870 81
1777553875 81
1777553880 81
1777553885 81
1777553890 81
1777553895 81
1777553900 81
1777553905 86
1777553910 86
1777553915 86
1777553920 86
1777553925 86
1777553930 84
1777553935 84
1777553940 84
```
</details>

---

