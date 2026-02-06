---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-06 09:39:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770388395 32
1770388400 32
1770388405 32
1770388410 32
1770388415 32
1770388420 30
1770388425 30
1770388430 30
1770388435 30
1770388440 30
1770388445 30
1770388450 30
1770388455 30
1770388460 30
1770388465 30
1770388470 30
1770388475 30
1770388480 30
1770388485 30
1770388490 30
```
</details>

---

