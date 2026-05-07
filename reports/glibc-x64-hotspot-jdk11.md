---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 09:00:14 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 17-32 cores)</summary>

```
1778158405 18
1778158410 18
1778158415 18
1778158420 20
1778158425 20
1778158430 20
1778158435 20
1778158440 17
1778158445 17
1778158450 17
1778158455 17
1778158460 17
1778158465 17
1778158470 17
1778158475 17
1778158480 17
1778158485 17
1778158490 17
1778158495 17
1778158500 17
```
</details>

---

