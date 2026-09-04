---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 10:12:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 15 |
| Allocations | 208 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1788530883 32
1788530888 32
1788530893 32
1788530898 32
1788530903 32
1788530908 32
1788530913 32
1788530918 32
1788530923 32
1788530928 32
1788530933 32
1788530938 32
1788530943 32
1788530948 32
1788530953 32
1788530958 32
1788530963 32
1788530968 32
1788530973 32
1788530978 32
```
</details>

---

