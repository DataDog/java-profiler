---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:30:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1790090635 32
1790090640 32
1790090645 32
1790090650 32
1790090655 32
1790090660 32
1790090665 32
1790090670 32
1790090675 32
1790090680 32
1790090685 32
1790090690 32
1790090695 32
1790090700 32
1790090705 32
1790090710 32
1790090715 24
1790090720 24
1790090725 24
1790090730 24
```
</details>

---

