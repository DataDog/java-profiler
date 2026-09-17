---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:55:47 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 58-73 cores)</summary>

```
1789667365 73
1789667370 73
1789667375 73
1789667380 73
1789667385 73
1789667390 73
1789667395 73
1789667400 73
1789667405 58
1789667410 58
1789667415 58
1789667420 58
1789667425 58
1789667430 58
1789667435 58
1789667440 58
1789667445 58
1789667450 58
1789667455 58
1789667460 58
```
</details>

---

