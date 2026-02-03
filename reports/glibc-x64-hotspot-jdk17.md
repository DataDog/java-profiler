---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 11:36:26 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 985 |
| Sample Rate | 16.42/sec |
| Health Score | 1026% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (4 unique values: 71-77 cores)</summary>

```
1770136151 72
1770136156 72
1770136161 72
1770136166 72
1770136171 72
1770136176 72
1770136181 72
1770136186 72
1770136191 72
1770136196 77
1770136201 77
1770136206 72
1770136212 72
1770136217 72
1770136222 72
1770136227 72
1770136232 76
1770136237 76
1770136242 76
1770136247 76
```
</details>

---

