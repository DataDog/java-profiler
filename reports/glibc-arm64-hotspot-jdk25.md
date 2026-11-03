---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 06:24:34 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 14 |
| Allocations | 163 |

<details>
<summary>CPU Timeline (1 unique values: 25-25 cores)</summary>

```
1793704824 25
1793704829 25
1793704834 25
1793704839 25
1793704844 25
1793704849 25
1793704854 25
1793704859 25
1793704864 25
1793704869 25
1793704874 25
1793704879 25
1793704884 25
1793704889 25
1793704894 25
1793704899 25
1793704904 25
1793704909 25
1793704914 25
1793704919 25
```
</details>

---

