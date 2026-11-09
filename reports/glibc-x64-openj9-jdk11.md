---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 10:36:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 861 |
| Sample Rate | 14.35/sec |
| Health Score | 897% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794238231 92
1794238236 92
1794238241 92
1794238246 92
1794238251 92
1794238256 92
1794238261 92
1794238266 92
1794238271 92
1794238276 92
1794238281 92
1794238286 92
1794238291 92
1794238296 94
1794238301 94
1794238306 94
1794238311 94
1794238316 94
1794238321 94
1794238326 94
```
</details>

---

