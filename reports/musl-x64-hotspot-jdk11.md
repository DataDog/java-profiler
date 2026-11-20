---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 06:12:58 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 11 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (3 unique values: 60-70 cores)</summary>

```
1795172818 68
1795172823 68
1795172828 68
1795172833 68
1795172838 68
1795172843 68
1795172848 68
1795172853 68
1795172858 70
1795172863 70
1795172868 68
1795172873 68
1795172878 68
1795172883 68
1795172888 68
1795172893 68
1795172898 68
1795172903 68
1795172908 60
1795172913 60
```
</details>

---

