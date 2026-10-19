---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 07:26:48 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 52 |
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
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 48-52 cores)</summary>

```
1792408950 48
1792408955 48
1792408960 48
1792408965 48
1792408970 48
1792408975 48
1792408980 48
1792408985 48
1792408990 48
1792408995 48
1792409000 48
1792409005 48
1792409010 48
1792409015 48
1792409020 48
1792409025 48
1792409030 48
1792409035 48
1792409040 52
1792409045 52
```
</details>

---

