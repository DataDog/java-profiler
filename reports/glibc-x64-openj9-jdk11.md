---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 17:16:30 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 952 |
| Sample Rate | 15.87/sec |
| Health Score | 992% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (5 unique values: 76-90 cores)</summary>

```
1794435152 90
1794435157 90
1794435162 90
1794435167 90
1794435172 90
1794435177 90
1794435182 90
1794435187 90
1794435192 90
1794435197 90
1794435202 90
1794435207 90
1794435212 90
1794435217 90
1794435222 90
1794435227 89
1794435232 89
1794435237 80
1794435242 80
1794435247 80
```
</details>

---

