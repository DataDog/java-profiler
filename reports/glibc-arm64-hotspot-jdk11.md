---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 10:12:47 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 10 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1788530829 24
1788530834 24
1788530839 24
1788530844 24
1788530849 24
1788530854 24
1788530859 24
1788530864 24
1788530869 24
1788530874 24
1788530879 24
1788530884 44
1788530889 44
1788530894 44
1788530899 44
1788530904 44
1788530909 44
1788530914 44
1788530919 44
1788530924 44
```
</details>

---

