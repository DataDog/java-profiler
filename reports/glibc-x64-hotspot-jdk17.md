---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 10:21:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1795447020 29
1795447025 29
1795447030 27
1795447035 27
1795447040 27
1795447045 27
1795447050 27
1795447055 27
1795447060 27
1795447065 27
1795447070 27
1795447075 27
1795447080 27
1795447085 27
1795447090 27
1795447095 27
1795447100 27
1795447105 27
1795447110 27
1795447115 27
```
</details>

---

