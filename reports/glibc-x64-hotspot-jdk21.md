---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-22 14:20:07 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1787422565 41
1787422570 41
1787422575 41
1787422580 41
1787422585 41
1787422590 41
1787422595 41
1787422600 41
1787422605 41
1787422610 41
1787422615 41
1787422620 41
1787422625 41
1787422630 41
1787422635 41
1787422640 46
1787422645 46
1787422650 46
1787422655 46
1787422660 46
```
</details>

---

