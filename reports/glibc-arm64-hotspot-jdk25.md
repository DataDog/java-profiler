---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 19:04:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1793141988 51
1793141993 51
1793141998 51
1793142003 51
1793142008 51
1793142013 51
1793142018 64
1793142023 64
1793142028 64
1793142033 64
1793142038 64
1793142043 64
1793142048 64
1793142053 64
1793142058 64
1793142063 64
1793142068 64
1793142073 64
1793142078 53
1793142083 53
```
</details>

---

