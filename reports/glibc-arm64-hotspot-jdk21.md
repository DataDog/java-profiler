---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-04 10:05:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (3 unique values: 20-40 cores)</summary>

```
1788530453 20
1788530458 20
1788530463 20
1788530468 20
1788530473 20
1788530478 20
1788530483 20
1788530488 20
1788530493 20
1788530498 20
1788530503 32
1788530508 32
1788530513 20
1788530518 20
1788530523 40
1788530528 40
1788530533 40
1788530538 40
1788530543 40
1788530548 40
```
</details>

---

