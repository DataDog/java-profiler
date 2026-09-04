---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-04 14:55:27 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 917 |
| Sample Rate | 15.28/sec |
| Health Score | 955% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 61-69 cores)</summary>

```
1788547910 69
1788547915 69
1788547920 69
1788547925 69
1788547930 69
1788547935 69
1788547940 69
1788547945 69
1788547950 69
1788547955 69
1788547960 61
1788547965 61
1788547970 61
1788547975 61
1788547980 61
1788547985 61
1788547990 61
1788547995 61
1788548000 61
1788548005 61
```
</details>

---

