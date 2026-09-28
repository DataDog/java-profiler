---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 09:39:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (6 unique values: 49-96 cores)</summary>

```
1790602552 51
1790602557 51
1790602562 51
1790602567 51
1790602572 51
1790602577 49
1790602582 49
1790602587 59
1790602592 59
1790602597 59
1790602602 61
1790602607 61
1790602612 94
1790602617 94
1790602622 94
1790602627 96
1790602632 96
1790602637 96
1790602642 96
1790602647 96
```
</details>

---

