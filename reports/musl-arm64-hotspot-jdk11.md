---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 10:05:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788530434 64
1788530439 64
1788530444 64
1788530449 64
1788530454 64
1788530459 64
1788530464 64
1788530469 64
1788530474 64
1788530479 64
1788530484 64
1788530489 64
1788530494 64
1788530499 64
1788530504 64
1788530509 64
1788530514 64
1788530520 64
1788530525 64
1788530530 64
```
</details>

---

