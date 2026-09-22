---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:34:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 8 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 17-27 cores)</summary>

```
1790090864 17
1790090869 17
1790090874 17
1790090879 17
1790090884 17
1790090889 17
1790090894 17
1790090899 27
1790090904 27
1790090909 17
1790090914 17
1790090919 17
1790090924 17
1790090929 22
1790090934 22
1790090939 22
1790090944 22
1790090949 22
1790090954 22
1790090959 22
```
</details>

---

