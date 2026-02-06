---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-06 09:39:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770388435 32
1770388440 32
1770388445 32
1770388450 32
1770388455 32
1770388460 32
1770388465 32
1770388470 32
1770388475 32
1770388480 32
1770388485 32
1770388490 32
1770388495 32
1770388500 32
1770388505 32
1770388510 32
1770388515 30
1770388520 30
1770388525 32
1770388530 32
```
</details>

---

