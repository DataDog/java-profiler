---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 16:43:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 73-81 cores)</summary>

```
1794001090 81
1794001095 81
1794001100 73
1794001105 73
1794001110 73
1794001115 73
1794001120 73
1794001125 73
1794001130 73
1794001135 73
1794001140 73
1794001145 73
1794001150 73
1794001155 73
1794001160 73
1794001165 73
1794001170 73
1794001175 73
1794001180 73
1794001185 73
```
</details>

---

