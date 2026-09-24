---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:38:23 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (5 unique values: 58-96 cores)</summary>

```
1790238875 58
1790238880 58
1790238885 58
1790238890 60
1790238895 60
1790238900 96
1790238905 96
1790238910 96
1790238915 96
1790238920 94
1790238925 94
1790238930 94
1790238935 94
1790238940 94
1790238945 94
1790238950 94
1790238955 94
1790238960 94
1790238965 94
1790238970 90
```
</details>

---

