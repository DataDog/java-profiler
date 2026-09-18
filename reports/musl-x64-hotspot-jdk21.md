---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:50:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 13-17 cores)</summary>

```
1789738894 13
1789738899 13
1789738904 13
1789738909 13
1789738914 13
1789738919 13
1789738924 13
1789738929 13
1789738934 13
1789738939 15
1789738944 15
1789738949 15
1789738954 15
1789738959 17
1789738964 17
1789738969 17
1789738974 17
1789738979 17
1789738984 17
1789738989 17
```
</details>

---

