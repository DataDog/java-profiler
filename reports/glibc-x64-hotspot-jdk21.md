---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-15 05:47:13 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 39-76 cores)</summary>

```
1786786948 39
1786786953 39
1786786958 39
1786786963 39
1786786968 41
1786786973 41
1786786978 41
1786786983 41
1786786988 41
1786786993 41
1786786998 61
1786787003 61
1786787008 76
1786787013 76
1786787018 76
1786787023 76
1786787028 76
1786787033 76
1786787038 76
1786787043 76
```
</details>

---

