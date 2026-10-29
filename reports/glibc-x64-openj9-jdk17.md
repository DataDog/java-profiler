---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 16:31:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1793305595 61
1793305600 61
1793305605 63
1793305610 63
1793305615 63
1793305620 63
1793305625 63
1793305630 63
1793305635 63
1793305640 63
1793305645 63
1793305650 63
1793305655 63
1793305660 63
1793305665 63
1793305670 63
1793305675 63
1793305680 63
1793305685 63
1793305690 63
```
</details>

---

