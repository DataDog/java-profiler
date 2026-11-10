---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 13:30:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 14 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1794334833 48
1794334838 48
1794334843 48
1794334848 48
1794334853 48
1794334858 44
1794334863 44
1794334868 44
1794334873 44
1794334878 44
1794334883 44
1794334888 40
1794334893 40
1794334898 40
1794334903 40
1794334908 40
1794334913 40
1794334918 40
1794334923 40
1794334928 40
```
</details>

---

