---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 11:20:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 75-84 cores)</summary>

```
1786029375 84
1786029380 84
1786029385 84
1786029390 84
1786029395 82
1786029400 82
1786029405 82
1786029410 82
1786029415 79
1786029420 79
1786029425 79
1786029430 79
1786029435 79
1786029440 77
1786029445 77
1786029450 77
1786029455 77
1786029460 75
1786029465 75
1786029470 75
```
</details>

---

