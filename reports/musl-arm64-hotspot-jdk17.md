---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788530788 59
1788530793 59
1788530798 59
1788530803 59
1788530808 59
1788530813 59
1788530818 59
1788530823 59
1788530828 59
1788530833 59
1788530838 59
1788530843 59
1788530848 64
1788530853 64
1788530858 64
1788530863 64
1788530868 64
1788530873 64
1788530878 64
1788530883 64
```
</details>

---

