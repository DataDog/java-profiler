---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:30:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1795011977 28
1795011982 28
1795011987 32
1795011992 32
1795011997 30
1795012002 30
1795012007 30
1795012012 30
1795012017 30
1795012022 30
1795012028 30
1795012033 30
1795012038 30
1795012043 30
1795012048 30
1795012053 30
1795012058 30
1795012063 30
1795012068 30
1795012073 30
```
</details>

---

