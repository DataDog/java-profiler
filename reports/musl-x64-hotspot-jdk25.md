---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 07:11:26 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 50-71 cores)</summary>

```
1795694818 50
1795694823 50
1795694828 50
1795694833 50
1795694838 50
1795694843 50
1795694848 50
1795694853 50
1795694858 67
1795694863 67
1795694868 67
1795694873 52
1795694878 52
1795694883 71
1795694888 71
1795694893 71
1795694898 71
1795694903 71
1795694908 71
1795694913 71
```
</details>

---

