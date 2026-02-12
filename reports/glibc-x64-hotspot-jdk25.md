---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-12 13:12:33 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 924 |
| Sample Rate | 15.40/sec |
| Health Score | 962% |
| Threads | 12 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 21-26 cores)</summary>

```
1770919665 23
1770919670 23
1770919675 23
1770919680 21
1770919685 21
1770919690 21
1770919695 21
1770919700 21
1770919705 21
1770919710 21
1770919715 23
1770919720 23
1770919725 26
1770919730 26
1770919735 26
1770919740 26
1770919745 26
1770919750 26
1770919755 26
1770919760 26
```
</details>

---

