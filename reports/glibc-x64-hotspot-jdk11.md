---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 10:24:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 85-94 cores)</summary>

```
1795533348 87
1795533353 87
1795533358 87
1795533363 87
1795533368 87
1795533373 87
1795533378 87
1795533383 87
1795533388 85
1795533393 85
1795533398 85
1795533403 94
1795533408 94
1795533413 92
1795533418 92
1795533423 92
1795533428 92
1795533433 92
1795533438 92
1795533443 92
```
</details>

---

