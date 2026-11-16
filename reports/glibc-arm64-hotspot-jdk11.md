---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 19:11:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 11 |
| Allocations | 183 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 11 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794787560 36
1794787565 36
1794787570 36
1794787575 36
1794787580 36
1794787585 36
1794787590 36
1794787595 36
1794787600 36
1794787605 36
1794787610 36
1794787615 36
1794787620 36
1794787625 48
1794787630 48
1794787635 48
1794787640 48
1794787645 48
1794787650 48
1794787655 48
```
</details>

---

