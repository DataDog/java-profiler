---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 16:43:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1008 |
| Sample Rate | 16.80/sec |
| Health Score | 1050% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1794001090 64
1794001095 64
1794001100 64
1794001105 64
1794001110 64
1794001115 64
1794001120 62
1794001125 62
1794001130 62
1794001135 62
1794001140 62
1794001145 62
1794001150 62
1794001155 62
1794001160 62
1794001165 62
1794001170 62
1794001175 62
1794001180 62
1794001185 62
```
</details>

---

