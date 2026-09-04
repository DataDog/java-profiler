---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1788530881 94
1788530886 94
1788530891 94
1788530896 94
1788530901 94
1788530906 94
1788530911 94
1788530916 94
1788530921 94
1788530926 96
1788530931 96
1788530936 96
1788530941 92
1788530946 92
1788530951 92
1788530956 92
1788530961 92
1788530966 92
1788530971 92
1788530976 92
```
</details>

---

