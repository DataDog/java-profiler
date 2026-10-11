---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-11 15:43:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1791747565 34
1791747570 34
1791747575 34
1791747580 34
1791747585 29
1791747590 29
1791747595 29
1791747600 29
1791747605 29
1791747610 29
1791747615 29
1791747620 29
1791747625 29
1791747630 29
1791747635 29
1791747640 29
1791747645 29
1791747650 29
1791747655 29
1791747660 29
```
</details>

---

