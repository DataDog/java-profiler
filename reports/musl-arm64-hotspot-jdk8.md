---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-27 00:56:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 53-59 cores)</summary>

```
1787806342 54
1787806347 53
1787806352 53
1787806357 53
1787806362 53
1787806367 53
1787806372 53
1787806377 53
1787806382 54
1787806387 54
1787806392 54
1787806397 54
1787806402 54
1787806407 54
1787806412 54
1787806417 54
1787806422 59
1787806427 59
1787806432 59
1787806437 59
```
</details>

---

