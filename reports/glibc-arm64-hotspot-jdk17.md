---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 10:12:47 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 14 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (5 unique values: 18-34 cores)</summary>

```
1788530834 32
1788530839 32
1788530844 34
1788530849 34
1788530854 34
1788530859 34
1788530864 34
1788530869 34
1788530874 34
1788530879 34
1788530884 34
1788530889 34
1788530894 34
1788530899 34
1788530904 26
1788530909 26
1788530914 26
1788530919 26
1788530924 26
1788530929 22
```
</details>

---

