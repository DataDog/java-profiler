---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 11:49:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 12 |
| Allocations | 200 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1791992524 29
1791992529 9
1791992534 9
1791992539 9
1791992544 9
1791992549 9
1791992554 9
1791992559 9
1791992564 9
1791992569 9
1791992574 9
1791992579 9
1791992584 9
1791992589 9
1791992594 9
1791992599 9
1791992604 9
1791992609 9
1791992614 9
1791992619 9
```
</details>

---

