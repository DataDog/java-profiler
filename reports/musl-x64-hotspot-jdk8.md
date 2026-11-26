---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-26 07:11:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 38 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1795694815 68
1795694820 68
1795694825 68
1795694830 66
1795694835 66
1795694840 66
1795694845 66
1795694850 66
1795694855 66
1795694860 66
1795694865 66
1795694870 66
1795694875 66
1795694880 66
1795694885 66
1795694890 66
1795694895 66
1795694900 66
1795694905 66
1795694910 66
```
</details>

---

