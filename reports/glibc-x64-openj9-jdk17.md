---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 12:37:05 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794936750 30
1794936755 30
1794936760 30
1794936765 30
1794936770 30
1794936775 30
1794936780 30
1794936785 30
1794936790 30
1794936795 30
1794936800 30
1794936805 32
1794936810 32
1794936815 30
1794936820 30
1794936825 30
1794936830 30
1794936835 30
1794936840 30
1794936845 30
```
</details>

---

