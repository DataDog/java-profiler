---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 12:51:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1770140771 23
1770140776 23
1770140781 32
1770140786 32
1770140791 32
1770140796 32
1770140801 32
1770140806 32
1770140811 32
1770140816 32
1770140821 32
1770140826 32
1770140831 32
1770140836 32
1770140841 32
1770140846 32
1770140851 32
1770140856 32
1770140861 32
1770140866 32
```
</details>

---

