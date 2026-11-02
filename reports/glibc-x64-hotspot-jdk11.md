---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:22:54 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793621891 30
1793621896 30
1793621901 30
1793621906 30
1793621911 30
1793621916 30
1793621921 30
1793621926 30
1793621931 30
1793621936 30
1793621941 30
1793621946 30
1793621951 30
1793621956 32
1793621961 32
1793621966 32
1793621971 32
1793621976 32
1793621981 32
1793621986 32
```
</details>

---

