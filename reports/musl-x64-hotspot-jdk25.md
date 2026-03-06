---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-06 11:13:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 10 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 22-32 cores)</summary>

```
1772813276 32
1772813281 32
1772813286 29
1772813291 29
1772813296 29
1772813301 29
1772813306 29
1772813311 29
1772813316 24
1772813321 24
1772813326 24
1772813331 24
1772813336 24
1772813341 24
1772813346 24
1772813351 24
1772813356 24
1772813361 22
1772813366 22
1772813371 22
```
</details>

---

