---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-15 01:03:23 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 21-32 cores)</summary>

```
1792040347 21
1792040352 21
1792040357 21
1792040362 23
1792040367 23
1792040372 23
1792040377 23
1792040382 23
1792040387 23
1792040392 23
1792040397 23
1792040403 23
1792040408 23
1792040413 23
1792040418 23
1792040423 23
1792040428 32
1792040433 32
1792040438 32
1792040443 32
```
</details>

---

