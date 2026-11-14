---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 05:55:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 61-81 cores)</summary>

```
1794653427 81
1794653432 81
1794653437 81
1794653442 81
1794653447 81
1794653452 81
1794653457 81
1794653462 81
1794653467 81
1794653472 81
1794653477 81
1794653482 81
1794653487 81
1794653492 81
1794653497 81
1794653502 61
1794653507 61
1794653512 61
1794653517 61
1794653522 61
```
</details>

---

