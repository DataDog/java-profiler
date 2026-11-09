---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 16:18:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 10 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794258945 34
1794258950 34
1794258955 34
1794258960 34
1794258965 34
1794258970 34
1794258975 34
1794258980 34
1794258985 34
1794258990 39
1794258995 39
1794259000 39
1794259005 39
1794259010 39
1794259015 39
1794259020 39
1794259025 39
1794259030 39
1794259035 39
1794259040 39
```
</details>

---

