---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 04:52:46 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 74-96 cores)</summary>

```
1770111859 78
1770111864 78
1770111869 78
1770111874 78
1770111879 78
1770111884 78
1770111889 76
1770111894 76
1770111899 74
1770111904 74
1770111909 74
1770111914 74
1770111919 74
1770111924 74
1770111929 74
1770111934 74
1770111939 74
1770111944 78
1770111949 78
1770111954 78
```
</details>

---

