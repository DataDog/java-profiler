---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 13:29:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 57-64 cores)</summary>

```
1794939903 57
1794939908 57
1794939913 57
1794939918 64
1794939923 64
1794939928 64
1794939933 64
1794939938 64
1794939943 64
1794939948 64
1794939953 64
1794939958 64
1794939963 64
1794939968 64
1794939973 64
1794939978 64
1794939983 64
1794939989 64
1794939994 64
1794939999 64
```
</details>

---

