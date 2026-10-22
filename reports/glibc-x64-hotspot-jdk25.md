---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:01:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792670270 32
1792670275 32
1792670280 32
1792670285 32
1792670290 32
1792670295 32
1792670300 32
1792670305 32
1792670310 32
1792670315 32
1792670320 32
1792670325 32
1792670330 32
1792670335 32
1792670340 32
1792670345 32
1792670350 32
1792670355 32
1792670360 32
1792670365 32
```
</details>

---

