---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 10:59:15 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 22-25 cores)</summary>

```
1793721310 22
1793721315 22
1793721320 22
1793721325 22
1793721330 22
1793721335 25
1793721340 25
1793721345 25
1793721350 25
1793721355 25
1793721360 25
1793721365 25
1793721370 25
1793721375 25
1793721380 25
1793721385 25
1793721390 25
1793721395 25
1793721400 25
1793721405 25
```
</details>

---

