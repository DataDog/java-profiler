---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-26 11:54:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 78-85 cores)</summary>

```
1795711803 80
1795711808 80
1795711813 80
1795711818 80
1795711823 80
1795711828 78
1795711833 78
1795711838 78
1795711843 78
1795711848 78
1795711853 78
1795711858 78
1795711863 78
1795711868 78
1795711873 81
1795711878 81
1795711883 83
1795711888 83
1795711893 83
1795711898 85
```
</details>

---

