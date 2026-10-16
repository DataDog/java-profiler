---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 05:17:21 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 9-32 cores)</summary>

```
1792141950 30
1792141955 30
1792141960 30
1792141965 32
1792141970 32
1792141975 11
1792141980 11
1792141985 9
1792141990 9
1792141995 9
1792142000 9
1792142005 9
1792142010 9
1792142015 9
1792142020 9
1792142025 9
1792142030 9
1792142035 9
1792142040 9
1792142045 9
```
</details>

---

