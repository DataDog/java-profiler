---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 03:42:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794559015 43
1794559020 43
1794559025 43
1794559030 43
1794559035 43
1794559040 43
1794559045 43
1794559050 43
1794559055 43
1794559060 43
1794559065 43
1794559070 43
1794559075 43
1794559080 43
1794559085 43
1794559090 43
1794559095 43
1794559100 43
1794559105 43
1794559110 48
```
</details>

---

