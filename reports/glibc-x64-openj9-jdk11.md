---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:19:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1794582895 63
1794582900 63
1794582905 63
1794582910 63
1794582915 63
1794582920 61
1794582925 61
1794582930 61
1794582935 61
1794582940 61
1794582945 61
1794582950 59
1794582955 59
1794582960 59
1794582965 59
1794582970 59
1794582975 59
1794582980 59
1794582985 59
1794582990 59
```
</details>

---

