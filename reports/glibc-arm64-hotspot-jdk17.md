---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 07:23:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 15 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794917966 46
1794917971 46
1794917976 46
1794917981 46
1794917986 51
1794917991 51
1794917996 51
1794918001 51
1794918006 51
1794918011 51
1794918017 51
1794918022 51
1794918027 51
1794918032 51
1794918037 51
1794918042 51
1794918047 51
1794918052 51
1794918057 51
1794918062 51
```
</details>

---

