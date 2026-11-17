---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 07:40:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 11 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (4 unique values: 36-40 cores)</summary>

```
1794918824 39
1794918829 40
1794918834 40
1794918839 40
1794918844 38
1794918849 38
1794918854 38
1794918859 38
1794918864 38
1794918869 38
1794918874 38
1794918879 38
1794918884 38
1794918889 38
1794918894 38
1794918899 38
1794918904 38
1794918909 38
1794918914 38
1794918919 38
```
</details>

---

