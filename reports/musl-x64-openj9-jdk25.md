---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-26 09:45:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 57-79 cores)</summary>

```
1787751584 61
1787751589 61
1787751594 61
1787751599 61
1787751604 61
1787751609 61
1787751614 61
1787751619 59
1787751624 59
1787751629 59
1787751634 59
1787751639 59
1787751644 59
1787751649 57
1787751654 57
1787751659 57
1787751664 57
1787751669 57
1787751674 57
1787751679 57
```
</details>

---

