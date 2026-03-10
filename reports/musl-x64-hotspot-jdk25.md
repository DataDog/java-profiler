---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-10 13:36:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 11 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 13 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 59-87 cores)</summary>

```
1773163855 66
1773163860 66
1773163865 66
1773163870 66
1773163875 66
1773163880 61
1773163885 61
1773163890 61
1773163895 61
1773163900 61
1773163905 61
1773163910 61
1773163915 87
1773163920 87
1773163925 61
1773163930 61
1773163935 61
1773163940 61
1773163945 61
1773163950 61
```
</details>

---

