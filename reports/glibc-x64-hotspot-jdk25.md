---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:34:56 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 57-65 cores)</summary>

```
1790090887 57
1790090892 57
1790090897 57
1790090902 65
1790090907 65
1790090912 65
1790090917 65
1790090922 65
1790090927 65
1790090932 65
1790090937 65
1790090942 65
1790090947 65
1790090952 65
1790090957 65
1790090962 65
1790090967 65
1790090972 65
1790090977 65
1790090982 65
```
</details>

---

