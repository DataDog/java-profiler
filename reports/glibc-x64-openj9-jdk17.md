---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:01:54 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (4 unique values: 77-88 cores)</summary>

```
1794480915 77
1794480920 77
1794480925 82
1794480930 82
1794480935 82
1794480940 82
1794480945 84
1794480950 84
1794480955 88
1794480960 88
1794480965 88
1794480970 88
1794480975 88
1794480980 88
1794480985 88
1794480990 88
1794480995 88
1794481000 88
1794481005 88
1794481010 88
```
</details>

---

