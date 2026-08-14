---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-14 01:01:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 35-70 cores)</summary>

```
1786683286 35
1786683291 37
1786683296 37
1786683301 35
1786683306 35
1786683311 35
1786683316 35
1786683321 35
1786683326 35
1786683331 37
1786683336 37
1786683341 37
1786683346 37
1786683351 37
1786683356 37
1786683361 70
1786683366 70
1786683371 70
1786683377 70
1786683382 70
```
</details>

---

