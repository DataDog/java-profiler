---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-27 21:22:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 7 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1790558304 13
1790558309 13
1790558315 18
1790558320 18
1790558325 18
1790558330 18
1790558335 18
1790558340 18
1790558345 18
1790558350 18
1790558355 18
1790558360 18
1790558365 18
1790558370 18
1790558375 18
1790558380 18
1790558385 18
1790558390 18
1790558395 18
1790558400 18
```
</details>

---

