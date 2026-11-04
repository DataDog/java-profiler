---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 80-89 cores)</summary>

```
1793829478 80
1793829483 80
1793829488 80
1793829493 80
1793829498 80
1793829503 82
1793829508 82
1793829513 82
1793829518 82
1793829523 82
1793829528 82
1793829533 82
1793829538 84
1793829543 84
1793829548 84
1793829553 84
1793829558 84
1793829563 84
1793829568 84
1793829573 84
```
</details>

---

