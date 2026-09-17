---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 05:57:22 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 917 |
| Sample Rate | 15.28/sec |
| Health Score | 955% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 73-75 cores)</summary>

```
1789638783 73
1789638788 73
1789638793 73
1789638798 73
1789638803 73
1789638808 73
1789638813 73
1789638818 73
1789638823 73
1789638828 73
1789638833 73
1789638838 75
1789638843 75
1789638848 75
1789638853 75
1789638858 75
1789638863 75
1789638868 75
1789638873 75
1789638878 75
```
</details>

---

