---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-10 13:55:47 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 11 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 13 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 83-92 cores)</summary>

```
1773165053 90
1773165058 90
1773165063 90
1773165068 90
1773165073 90
1773165078 90
1773165083 90
1773165088 88
1773165093 88
1773165098 88
1773165103 90
1773165108 90
1773165113 90
1773165118 92
1773165123 92
1773165128 92
1773165133 92
1773165138 92
1773165143 92
1773165148 92
```
</details>

---

