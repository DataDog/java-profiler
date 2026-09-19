---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-19 05:47:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 69-96 cores)</summary>

```
1789811015 94
1789811020 94
1789811025 96
1789811030 96
1789811035 96
1789811040 96
1789811045 96
1789811050 96
1789811055 96
1789811060 96
1789811066 96
1789811071 96
1789811076 96
1789811081 96
1789811086 96
1789811091 96
1789811096 96
1789811101 96
1789811106 96
1789811111 96
```
</details>

---

