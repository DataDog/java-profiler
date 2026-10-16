---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:17:24 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (6 unique values: 50-62 cores)</summary>

```
1792141932 61
1792141937 62
1792141942 62
1792141947 62
1792141952 62
1792141957 62
1792141962 62
1792141967 62
1792141972 62
1792141977 60
1792141982 60
1792141987 60
1792141992 60
1792141997 55
1792142002 55
1792142007 55
1792142012 55
1792142017 55
1792142022 57
1792142027 57
```
</details>

---

