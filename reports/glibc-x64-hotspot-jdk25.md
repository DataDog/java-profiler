---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-13 06:34:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 48-70 cores)</summary>

```
1786617038 48
1786617043 48
1786617048 70
1786617053 70
1786617058 70
1786617063 70
1786617068 70
1786617073 70
1786617078 70
1786617083 70
1786617088 70
1786617093 70
1786617098 70
1786617103 70
1786617108 68
1786617113 68
1786617118 68
1786617123 68
1786617128 68
1786617133 68
```
</details>

---

