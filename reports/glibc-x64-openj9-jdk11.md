---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-31 06:37:58 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 70-90 cores)</summary>

```
1788172345 76
1788172350 76
1788172355 76
1788172360 76
1788172365 76
1788172370 76
1788172375 76
1788172380 76
1788172385 76
1788172390 76
1788172395 76
1788172400 76
1788172405 76
1788172410 76
1788172415 76
1788172420 70
1788172425 70
1788172430 70
1788172435 70
1788172440 90
```
</details>

---

