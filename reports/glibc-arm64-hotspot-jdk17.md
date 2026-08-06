---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 08:23:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 7 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 21-34 cores)</summary>

```
1786018795 21
1786018800 21
1786018805 21
1786018810 21
1786018815 21
1786018820 21
1786018825 21
1786018830 21
1786018835 21
1786018840 21
1786018845 21
1786018850 21
1786018855 21
1786018860 21
1786018865 21
1786018870 21
1786018875 21
1786018880 21
1786018885 21
1786018890 32
```
</details>

---

