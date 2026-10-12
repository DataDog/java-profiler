---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-12 04:31:33 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (4 unique values: 27-34 cores)</summary>

```
1791793600 31
1791793605 31
1791793610 31
1791793615 31
1791793620 31
1791793625 31
1791793630 34
1791793635 34
1791793640 34
1791793645 34
1791793650 34
1791793655 34
1791793660 34
1791793665 34
1791793670 33
1791793675 33
1791793680 33
1791793685 33
1791793690 33
1791793695 33
```
</details>

---

