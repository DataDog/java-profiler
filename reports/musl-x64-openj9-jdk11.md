---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 09:21:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 77-86 cores)</summary>

```
1794838635 77
1794838640 77
1794838645 77
1794838650 77
1794838655 77
1794838660 77
1794838665 77
1794838670 79
1794838675 79
1794838680 79
1794838685 79
1794838690 79
1794838695 84
1794838700 84
1794838705 84
1794838710 84
1794838715 84
1794838720 84
1794838725 86
1794838730 86
```
</details>

---

