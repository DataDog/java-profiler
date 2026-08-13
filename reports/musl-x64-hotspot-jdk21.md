---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-13 04:53:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 50-70 cores)</summary>

```
1786610839 50
1786610844 50
1786610849 50
1786610854 50
1786610859 50
1786610864 68
1786610869 68
1786610874 68
1786610879 68
1786610884 68
1786610889 68
1786610894 68
1786610899 68
1786610904 68
1786610909 68
1786610914 70
1786610919 70
1786610924 70
1786610929 70
1786610934 70
```
</details>

---

