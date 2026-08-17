---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 09:10:33 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1786971600 96
1786971605 96
1786971610 96
1786971615 94
1786971620 94
1786971625 94
1786971630 94
1786971635 94
1786971640 94
1786971645 94
1786971650 94
1786971655 96
1786971660 96
1786971665 96
1786971670 96
1786971675 96
1786971680 96
1786971685 96
1786971690 96
1786971695 96
```
</details>

---

