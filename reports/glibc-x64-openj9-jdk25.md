---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-05 05:01:07 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 958 |
| Sample Rate | 15.97/sec |
| Health Score | 998% |
| Threads | 12 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1770285113 32
1770285118 32
1770285123 32
1770285128 28
1770285133 28
1770285138 28
1770285143 28
1770285148 28
1770285153 28
1770285158 28
1770285163 28
1770285168 28
1770285173 28
1770285178 28
1770285183 28
1770285188 28
1770285193 28
1770285198 28
1770285203 28
1770285208 28
```
</details>

---

