---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 13:30:50 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 41-64 cores)</summary>

```
1794334855 64
1794334860 64
1794334865 64
1794334870 56
1794334875 56
1794334880 56
1794334885 56
1794334890 56
1794334895 56
1794334900 56
1794334905 56
1794334910 56
1794334915 56
1794334920 56
1794334925 56
1794334930 56
1794334935 56
1794334940 56
1794334945 56
1794334950 58
```
</details>

---

