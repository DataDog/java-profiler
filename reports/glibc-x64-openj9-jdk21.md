---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:02:49 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794927390 32
1794927395 32
1794927400 32
1794927405 32
1794927410 30
1794927416 30
1794927421 30
1794927426 30
1794927431 30
1794927436 30
1794927441 30
1794927446 30
1794927451 32
1794927456 32
1794927461 32
1794927466 32
1794927471 32
1794927476 32
1794927481 32
1794927486 32
```
</details>

---

