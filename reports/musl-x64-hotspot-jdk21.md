---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 02:36:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1790663433 11
1790663438 11
1790663443 11
1790663448 11
1790663453 11
1790663458 11
1790663463 11
1790663468 11
1790663473 11
1790663478 11
1790663483 11
1790663488 32
1790663493 32
1790663498 32
1790663503 32
1790663508 32
1790663513 32
1790663518 32
1790663523 32
1790663528 32
```
</details>

---

