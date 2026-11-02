---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-01 23:46:56 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 12 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1793594510 30
1793594515 30
1793594520 30
1793594525 30
1793594530 30
1793594535 30
1793594540 30
1793594545 30
1793594551 30
1793594556 30
1793594561 30
1793594566 30
1793594571 30
1793594576 30
1793594581 30
1793594586 30
1793594591 30
1793594596 30
1793594601 30
1793594606 30
```
</details>

---

