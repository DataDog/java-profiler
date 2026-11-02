---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 14:28:39 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793647466 30
1793647471 30
1793647476 30
1793647481 30
1793647486 30
1793647491 30
1793647496 30
1793647501 30
1793647506 32
1793647511 32
1793647516 32
1793647521 32
1793647526 32
1793647531 32
1793647536 30
1793647541 30
1793647546 30
1793647551 30
1793647556 30
1793647561 30
```
</details>

---

