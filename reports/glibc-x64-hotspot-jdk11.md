---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:21:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1795641381 69
1795641386 69
1795641391 69
1795641396 69
1795641401 69
1795641406 69
1795641411 69
1795641416 69
1795641421 69
1795641426 69
1795641431 69
1795641436 67
1795641441 67
1795641446 67
1795641451 67
1795641456 69
1795641461 69
1795641466 69
1795641471 69
1795641476 69
```
</details>

---

