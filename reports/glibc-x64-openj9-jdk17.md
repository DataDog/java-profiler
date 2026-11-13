---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 09:22:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (4 unique values: 86-91 cores)</summary>

```
1794579402 89
1794579407 89
1794579412 89
1794579417 89
1794579422 89
1794579427 89
1794579432 89
1794579437 89
1794579442 91
1794579447 91
1794579452 91
1794579457 88
1794579462 88
1794579467 88
1794579472 88
1794579477 88
1794579482 88
1794579487 88
1794579492 88
1794579497 88
```
</details>

---

