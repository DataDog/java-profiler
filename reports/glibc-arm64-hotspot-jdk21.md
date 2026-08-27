---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-27 00:56:03 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 14 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 20-26 cores)</summary>

```
1787806342 21
1787806347 21
1787806352 21
1787806357 26
1787806362 26
1787806367 26
1787806372 26
1787806377 22
1787806382 22
1787806387 22
1787806392 22
1787806397 22
1787806402 22
1787806407 22
1787806412 22
1787806417 22
1787806422 22
1787806427 22
1787806432 22
1787806437 21
```
</details>

---

