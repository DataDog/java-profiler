---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:56:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 76-83 cores)</summary>

```
1794325909 79
1794325914 79
1794325919 79
1794325924 79
1794325929 79
1794325934 79
1794325939 79
1794325944 79
1794325949 77
1794325954 77
1794325959 77
1794325964 77
1794325969 77
1794325974 77
1794325979 77
1794325984 77
1794325989 76
1794325994 76
1794325999 76
1794326004 76
```
</details>

---

