---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:48:06 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 33 |
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
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1791391395 48
1791391400 48
1791391405 48
1791391410 43
1791391415 43
1791391420 43
1791391425 43
1791391430 43
1791391435 43
1791391440 43
1791391445 43
1791391450 43
1791391455 43
1791391460 43
1791391465 43
1791391470 43
1791391475 43
1791391480 38
1791391485 38
1791391490 38
```
</details>

---

