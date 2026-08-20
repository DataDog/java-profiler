---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 12:31:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 75-81 cores)</summary>

```
1787243200 75
1787243205 75
1787243210 75
1787243215 75
1787243220 75
1787243225 75
1787243230 75
1787243235 75
1787243240 81
1787243245 81
1787243250 81
1787243255 81
1787243260 81
1787243265 81
1787243270 81
1787243275 81
1787243280 81
1787243285 81
1787243290 81
1787243295 81
```
</details>

---

