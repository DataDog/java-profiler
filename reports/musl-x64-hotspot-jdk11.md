---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 13:17:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 939 |
| Sample Rate | 15.65/sec |
| Health Score | 978% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 70-75 cores)</summary>

```
1778173866 72
1778173871 74
1778173876 74
1778173881 74
1778173886 74
1778173891 74
1778173896 74
1778173901 74
1778173906 74
1778173911 74
1778173916 74
1778173921 70
1778173926 70
1778173931 70
1778173936 70
1778173941 70
1778173946 70
1778173951 70
1778173956 70
1778173961 70
```
</details>

---

