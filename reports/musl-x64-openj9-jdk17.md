---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 04:33:10 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 72-96 cores)</summary>

```
1773217611 96
1773217616 96
1773217621 96
1773217626 96
1773217631 96
1773217636 96
1773217641 96
1773217646 72
1773217651 72
1773217656 72
1773217661 72
1773217666 72
1773217671 72
1773217676 72
1773217681 72
1773217686 72
1773217691 72
1773217696 72
1773217701 72
1773217706 72
```
</details>

---

