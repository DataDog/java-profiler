---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 07:29:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 40-44 cores)</summary>

```
1791372321 40
1791372326 40
1791372331 40
1791372336 44
1791372341 44
1791372346 44
1791372351 44
1791372356 44
1791372361 44
1791372366 44
1791372371 44
1791372376 44
1791372381 44
1791372386 44
1791372391 44
1791372396 44
1791372401 44
1791372406 42
1791372411 42
1791372416 42
```
</details>

---

