---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 12:51:46 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 15-27 cores)</summary>

```
1770140781 25
1770140786 25
1770140791 25
1770140796 25
1770140801 25
1770140806 25
1770140811 25
1770140816 25
1770140821 25
1770140826 24
1770140831 24
1770140836 24
1770140841 25
1770140846 25
1770140851 25
1770140856 25
1770140861 25
1770140866 25
1770140871 27
1770140876 27
```
</details>

---

