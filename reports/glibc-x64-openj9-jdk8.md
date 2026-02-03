---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-03 12:51:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1770140761 29
1770140766 29
1770140771 29
1770140776 29
1770140781 29
1770140786 29
1770140791 29
1770140796 29
1770140801 29
1770140806 29
1770140811 29
1770140816 29
1770140821 29
1770140826 29
1770140831 29
1770140836 29
1770140841 29
1770140846 29
1770140851 29
1770140856 27
```
</details>

---

