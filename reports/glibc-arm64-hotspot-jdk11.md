---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 08:37:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 12 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 954 |
| Sample Rate | 15.90/sec |
| Health Score | 994% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795440779 48
1795440784 48
1795440789 48
1795440794 48
1795440799 48
1795440804 48
1795440809 48
1795440814 48
1795440819 48
1795440824 48
1795440829 48
1795440834 48
1795440839 48
1795440844 48
1795440849 48
1795440854 48
1795440859 48
1795440864 43
1795440869 43
1795440874 43
```
</details>

---

