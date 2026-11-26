---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 11:54:37 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 5 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (3 unique values: 22-34 cores)</summary>

```
1795711803 34
1795711808 26
1795711813 26
1795711818 34
1795711823 34
1795711828 34
1795711833 34
1795711838 34
1795711843 34
1795711848 34
1795711853 34
1795711858 22
1795711863 22
1795711868 22
1795711873 22
1795711878 22
1795711883 22
1795711888 22
1795711893 22
1795711898 22
```
</details>

---

