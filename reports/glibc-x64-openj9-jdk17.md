---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:13:59 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 44-75 cores)</summary>

```
1789743338 51
1789743343 75
1789743348 75
1789743353 75
1789743358 75
1789743363 75
1789743368 75
1789743373 75
1789743378 75
1789743383 75
1789743388 75
1789743393 75
1789743398 75
1789743403 75
1789743408 75
1789743413 75
1789743418 44
1789743423 44
1789743428 44
1789743433 44
```
</details>

---

