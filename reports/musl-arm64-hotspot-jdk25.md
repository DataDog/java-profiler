---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 13:02:41 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1790787389 48
1790787394 48
1790787399 48
1790787404 48
1790787409 48
1790787414 48
1790787419 48
1790787424 48
1790787429 43
1790787434 43
1790787439 54
1790787444 54
1790787449 54
1790787454 54
1790787459 54
1790787464 54
1790787469 54
1790787474 54
1790787479 64
1790787484 64
```
</details>

---

