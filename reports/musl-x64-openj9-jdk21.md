---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:38:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 58-96 cores)</summary>

```
1790238852 58
1790238857 58
1790238862 58
1790238867 58
1790238872 58
1790238877 58
1790238882 58
1790238887 60
1790238892 60
1790238897 60
1790238902 96
1790238907 96
1790238912 96
1790238917 96
1790238922 94
1790238927 94
1790238932 94
1790238937 94
1790238942 94
1790238947 94
```
</details>

---

