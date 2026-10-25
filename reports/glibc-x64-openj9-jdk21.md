---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-25 08:54:34 EDT

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
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1792932538 30
1792932543 30
1792932548 30
1792932553 30
1792932558 30
1792932563 30
1792932568 30
1792932573 30
1792932578 30
1792932583 30
1792932588 30
1792932593 28
1792932598 28
1792932603 28
1792932608 28
1792932613 28
1792932618 28
1792932623 28
1792932628 28
1792932633 28
```
</details>

---

