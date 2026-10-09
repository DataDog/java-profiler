---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 05:55:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1791539338 36
1791539343 31
1791539348 31
1791539353 31
1791539358 31
1791539363 31
1791539368 31
1791539373 31
1791539378 31
1791539383 31
1791539388 31
1791539393 31
1791539398 31
1791539403 31
1791539408 31
1791539413 36
1791539418 36
1791539423 36
1791539428 36
1791539433 36
```
</details>

---

