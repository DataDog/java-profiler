---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-12 13:12:33 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 87-91 cores)</summary>

```
1770919615 87
1770919620 87
1770919625 87
1770919630 87
1770919635 87
1770919640 87
1770919645 87
1770919650 87
1770919655 87
1770919660 91
1770919665 91
1770919670 91
1770919675 91
1770919680 91
1770919685 91
1770919690 91
1770919695 91
1770919700 91
1770919705 91
1770919710 91
```
</details>

---

