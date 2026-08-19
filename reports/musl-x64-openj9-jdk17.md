---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-19 09:55:43 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 939 |
| Sample Rate | 15.65/sec |
| Health Score | 978% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 89-94 cores)</summary>

```
1787147507 94
1787147512 94
1787147517 94
1787147522 89
1787147527 89
1787147532 91
1787147537 91
1787147542 91
1787147547 91
1787147552 91
1787147557 91
1787147562 91
1787147567 91
1787147572 91
1787147577 91
1787147582 89
1787147587 89
1787147592 94
1787147597 94
1787147602 94
```
</details>

---

