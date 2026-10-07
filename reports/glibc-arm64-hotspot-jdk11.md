---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-07 07:29:46 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 11 |
| Allocations | 189 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1791372331 36
1791372336 36
1791372341 36
1791372346 36
1791372351 36
1791372356 36
1791372361 36
1791372366 36
1791372371 36
1791372376 36
1791372381 36
1791372386 36
1791372391 36
1791372396 36
1791372401 36
1791372406 36
1791372411 31
1791372416 31
1791372421 31
1791372426 31
```
</details>

---

