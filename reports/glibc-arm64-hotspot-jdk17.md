---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:07:01 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795111315 50
1795111320 50
1795111325 50
1795111330 50
1795111335 50
1795111340 50
1795111345 50
1795111350 50
1795111355 50
1795111360 50
1795111365 50
1795111370 50
1795111375 50
1795111380 50
1795111385 50
1795111390 50
1795111395 50
1795111400 50
1795111405 50
1795111410 50
```
</details>

---

