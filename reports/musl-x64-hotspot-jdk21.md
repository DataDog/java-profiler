---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 13:30:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 884 |
| Sample Rate | 14.73/sec |
| Health Score | 921% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 35-56 cores)</summary>

```
1794334833 56
1794334838 56
1794334843 56
1794334848 56
1794334853 56
1794334858 56
1794334863 56
1794334868 39
1794334873 39
1794334878 39
1794334883 39
1794334888 37
1794334893 37
1794334898 35
1794334903 35
1794334908 35
1794334913 35
1794334918 35
1794334923 35
1794334928 35
```
</details>

---

