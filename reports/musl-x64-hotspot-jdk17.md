---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 10:11:34 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 62-92 cores)</summary>

```
1788530857 62
1788530862 62
1788530867 62
1788530872 82
1788530877 82
1788530882 82
1788530887 82
1788530892 84
1788530897 84
1788530902 84
1788530907 84
1788530912 84
1788530917 84
1788530922 80
1788530927 80
1788530932 80
1788530937 80
1788530942 80
1788530947 92
1788530952 92
```
</details>

---

