---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-27 21:22:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-58 cores)</summary>

```
1790558276 28
1790558281 28
1790558286 28
1790558291 28
1790558296 28
1790558301 28
1790558306 28
1790558311 28
1790558316 28
1790558321 28
1790558326 28
1790558331 28
1790558336 28
1790558341 28
1790558346 58
1790558351 58
1790558356 58
1790558361 58
1790558366 58
1790558371 58
```
</details>

---

