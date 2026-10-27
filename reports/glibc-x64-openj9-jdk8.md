---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-27 07:00:16 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 59-69 cores)</summary>

```
1793098439 59
1793098444 59
1793098449 59
1793098454 59
1793098459 59
1793098464 69
1793098469 69
1793098474 69
1793098479 69
1793098484 69
1793098489 69
1793098494 69
1793098499 69
1793098504 69
1793098509 69
1793098514 69
1793098519 69
1793098524 69
1793098529 67
1793098534 67
```
</details>

---

