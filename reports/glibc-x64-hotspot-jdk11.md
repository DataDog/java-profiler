---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 21:05:21 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793930496 32
1793930501 32
1793930506 32
1793930511 32
1793930516 32
1793930521 32
1793930526 32
1793930531 32
1793930536 32
1793930541 32
1793930546 32
1793930551 32
1793930556 32
1793930561 32
1793930566 32
1793930571 32
1793930576 32
1793930581 32
1793930586 32
1793930591 32
```
</details>

---

