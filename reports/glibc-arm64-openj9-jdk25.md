---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 11 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (5 unique values: 18-34 cores)</summary>

```
1788530815 32
1788530820 32
1788530825 32
1788530830 32
1788530835 32
1788530840 32
1788530845 34
1788530850 34
1788530855 34
1788530860 34
1788530865 34
1788530870 34
1788530875 34
1788530880 34
1788530885 34
1788530890 34
1788530895 34
1788530900 34
1788530905 26
1788530910 26
```
</details>

---

