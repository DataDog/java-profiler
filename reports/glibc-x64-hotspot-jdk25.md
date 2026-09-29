---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 12:33:14 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 66-76 cores)</summary>

```
1790699321 66
1790699326 66
1790699331 66
1790699336 66
1790699341 76
1790699346 76
1790699351 76
1790699356 76
1790699361 76
1790699366 76
1790699371 76
1790699376 76
1790699381 76
1790699386 76
1790699391 76
1790699396 76
1790699401 76
1790699406 76
1790699411 76
1790699416 76
```
</details>

---

