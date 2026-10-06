---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 11:23:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1791299934 66
1791299940 66
1791299945 66
1791299950 66
1791299955 64
1791299960 64
1791299965 64
1791299970 64
1791299975 66
1791299980 66
1791299985 66
1791299990 66
1791299995 66
1791300000 66
1791300005 66
1791300010 66
1791300015 66
1791300020 66
1791300025 68
1791300030 68
```
</details>

---

