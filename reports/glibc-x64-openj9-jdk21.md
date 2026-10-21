---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 12:42:59 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 27-28 cores)</summary>

```
1792600680 28
1792600685 28
1792600690 28
1792600695 28
1792600700 28
1792600705 28
1792600710 28
1792600715 28
1792600720 28
1792600725 28
1792600730 28
1792600735 28
1792600740 28
1792600745 28
1792600750 28
1792600755 27
1792600760 27
1792600765 27
1792600770 27
1792600775 27
```
</details>

---

