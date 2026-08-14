---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-14 08:29:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1786710291 92
1786710296 92
1786710301 92
1786710306 92
1786710311 92
1786710316 92
1786710321 92
1786710326 92
1786710331 92
1786710336 92
1786710341 92
1786710346 92
1786710351 92
1786710356 92
1786710361 92
1786710366 92
1786710371 90
1786710376 90
1786710381 90
1786710386 90
```
</details>

---

