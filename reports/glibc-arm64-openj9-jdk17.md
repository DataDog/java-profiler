---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 07:14:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 25-59 cores)</summary>

```
1793880531 25
1793880536 25
1793880541 25
1793880546 25
1793880551 25
1793880556 25
1793880561 25
1793880566 59
1793880571 59
1793880576 59
1793880581 59
1793880586 25
1793880591 25
1793880596 25
1793880601 25
1793880606 25
1793880611 25
1793880616 25
1793880621 25
1793880626 25
```
</details>

---

