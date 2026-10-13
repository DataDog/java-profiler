---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 13:24:03 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1791911912 71
1791911917 71
1791911922 71
1791911927 71
1791911932 71
1791911937 71
1791911942 69
1791911947 69
1791911952 67
1791911957 67
1791911962 67
1791911967 67
1791911972 67
1791911977 67
1791911982 69
1791911987 69
1791911992 69
1791911997 69
1791912002 69
1791912007 69
```
</details>

---

