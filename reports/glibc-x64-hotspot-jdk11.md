---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:44:19 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1794584426 29
1794584431 29
1794584436 29
1794584441 29
1794584446 29
1794584451 29
1794584456 29
1794584461 29
1794584466 29
1794584471 29
1794584476 32
1794584481 32
1794584486 32
1794584491 32
1794584496 32
1794584501 32
1794584506 32
1794584511 32
1794584516 32
1794584521 32
```
</details>

---

