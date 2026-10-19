---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 07:24:41 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (2 unique values: 47-65 cores)</summary>

```
1792408790 47
1792408795 47
1792408800 47
1792408805 47
1792408810 47
1792408815 47
1792408820 47
1792408825 65
1792408830 65
1792408835 65
1792408840 65
1792408845 65
1792408850 65
1792408855 65
1792408860 65
1792408865 65
1792408870 65
1792408875 65
1792408880 65
1792408885 65
```
</details>

---

