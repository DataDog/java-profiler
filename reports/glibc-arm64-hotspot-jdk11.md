---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:07:06 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 46-59 cores)</summary>

```
1794502932 46
1794502937 51
1794502942 51
1794502947 46
1794502952 46
1794502957 46
1794502962 46
1794502967 46
1794502972 46
1794502977 46
1794502982 46
1794502987 46
1794502992 46
1794502997 59
1794503002 59
1794503007 46
1794503012 46
1794503017 51
1794503022 51
1794503027 51
```
</details>

---

