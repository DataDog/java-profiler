---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-12 13:12:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 79 |
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
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (4 unique values: 79-87 cores)</summary>

```
1770919625 87
1770919630 87
1770919635 87
1770919640 85
1770919645 85
1770919650 85
1770919655 85
1770919660 85
1770919665 85
1770919670 85
1770919675 85
1770919680 85
1770919685 85
1770919690 85
1770919695 85
1770919700 85
1770919705 85
1770919710 81
1770919715 81
1770919720 81
```
</details>

---

