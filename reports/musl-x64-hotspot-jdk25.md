---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 01:04:34 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 66-94 cores)</summary>

```
1787115595 88
1787115600 88
1787115605 88
1787115610 88
1787115615 88
1787115620 94
1787115625 94
1787115630 94
1787115635 94
1787115640 72
1787115645 72
1787115650 72
1787115655 72
1787115660 72
1787115665 72
1787115670 72
1787115675 66
1787115680 66
1787115685 68
1787115690 68
```
</details>

---

