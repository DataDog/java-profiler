---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-24 18:13:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 10 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1787609372 40
1787609377 40
1787609382 48
1787609387 48
1787609392 47
1787609397 47
1787609402 47
1787609407 47
1787609412 47
1787609417 47
1787609422 42
1787609427 42
1787609432 42
1787609437 42
1787609442 42
1787609447 43
1787609452 43
1787609457 43
1787609462 43
1787609467 43
```
</details>

---

