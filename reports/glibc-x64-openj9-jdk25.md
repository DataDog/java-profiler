---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 17:27:06 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 88-90 cores)</summary>

```
1792704089 90
1792704094 90
1792704099 90
1792704104 90
1792704109 90
1792704114 90
1792704119 90
1792704124 90
1792704129 90
1792704134 90
1792704139 90
1792704144 90
1792704149 90
1792704154 90
1792704159 90
1792704164 90
1792704169 90
1792704174 88
1792704179 88
1792704184 88
```
</details>

---

