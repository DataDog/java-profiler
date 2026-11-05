---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 07:14:26 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 52-71 cores)</summary>

```
1793880536 62
1793880541 62
1793880546 62
1793880551 62
1793880556 62
1793880561 62
1793880566 62
1793880571 62
1793880576 62
1793880581 62
1793880586 68
1793880591 68
1793880596 68
1793880601 68
1793880606 68
1793880611 68
1793880616 71
1793880621 71
1793880626 71
1793880631 71
```
</details>

---

