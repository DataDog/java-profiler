---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 60-74 cores)</summary>

```
1793829493 60
1793829498 60
1793829503 60
1793829508 60
1793829513 71
1793829518 71
1793829523 71
1793829528 71
1793829533 71
1793829538 71
1793829543 71
1793829548 71
1793829553 71
1793829558 71
1793829563 71
1793829568 71
1793829573 71
1793829578 71
1793829583 71
1793829588 71
```
</details>

---

