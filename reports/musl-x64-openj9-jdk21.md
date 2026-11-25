---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:39:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 83-92 cores)</summary>

```
1795606467 92
1795606472 92
1795606477 86
1795606482 86
1795606487 88
1795606492 88
1795606497 88
1795606502 88
1795606507 88
1795606512 88
1795606517 88
1795606522 83
1795606527 83
1795606532 83
1795606537 83
1795606542 83
1795606547 83
1795606552 83
1795606557 83
1795606562 83
```
</details>

---

