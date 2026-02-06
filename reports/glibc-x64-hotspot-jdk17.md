---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-06 09:39:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 55-85 cores)</summary>

```
1770388409 55
1770388414 55
1770388419 55
1770388424 55
1770388429 81
1770388434 81
1770388439 81
1770388444 81
1770388449 81
1770388454 85
1770388459 85
1770388464 85
1770388469 85
1770388474 85
1770388479 85
1770388484 85
1770388489 85
1770388494 85
1770388499 85
1770388504 85
```
</details>

---

