---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 08:53:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 40-64 cores)</summary>

```
1794318465 62
1794318470 62
1794318475 62
1794318480 64
1794318485 64
1794318490 64
1794318495 64
1794318500 64
1794318505 64
1794318510 64
1794318515 64
1794318520 64
1794318525 47
1794318530 47
1794318535 47
1794318540 47
1794318545 47
1794318550 47
1794318555 47
1794318560 47
```
</details>

---

