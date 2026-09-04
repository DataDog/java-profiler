---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-04 10:05:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 15 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788530461 48
1788530466 48
1788530471 48
1788530476 48
1788530481 48
1788530486 48
1788530491 43
1788530496 43
1788530501 43
1788530506 43
1788530511 43
1788530516 43
1788530521 43
1788530526 43
1788530531 43
1788530536 43
1788530541 43
1788530546 43
1788530551 43
1788530556 43
```
</details>

---

