---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:15:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 70-71 cores)</summary>

```
1794841845 71
1794841850 71
1794841855 71
1794841860 71
1794841865 71
1794841870 71
1794841875 71
1794841880 71
1794841885 71
1794841890 71
1794841895 71
1794841900 71
1794841905 71
1794841910 71
1794841915 71
1794841920 71
1794841925 70
1794841930 70
1794841935 70
1794841940 70
```
</details>

---

