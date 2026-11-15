---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 18:26:28 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 57-75 cores)</summary>

```
1794784900 57
1794784905 57
1794784910 57
1794784915 59
1794784920 59
1794784925 59
1794784930 59
1794784935 59
1794784940 59
1794784945 75
1794784950 75
1794784955 75
1794784960 75
1794784965 75
1794784970 75
1794784975 75
1794784980 75
1794784985 75
1794784990 75
1794784995 75
```
</details>

---

