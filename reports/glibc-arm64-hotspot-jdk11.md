---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 03:42:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 26-43 cores)</summary>

```
1794559045 26
1794559050 26
1794559055 26
1794559060 26
1794559065 26
1794559070 26
1794559075 26
1794559080 38
1794559085 38
1794559090 38
1794559095 38
1794559100 38
1794559105 38
1794559110 43
1794559115 43
1794559120 43
1794559126 43
1794559131 43
1794559136 43
1794559141 43
```
</details>

---

