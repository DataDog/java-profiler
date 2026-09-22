---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 05:59:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 11 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 34-44 cores)</summary>

```
1790070833 34
1790070838 34
1790070843 34
1790070848 34
1790070853 34
1790070858 34
1790070863 34
1790070868 39
1790070873 39
1790070878 39
1790070883 39
1790070888 39
1790070893 39
1790070898 39
1790070903 39
1790070908 39
1790070913 39
1790070918 39
1790070923 39
1790070928 39
```
</details>

---

