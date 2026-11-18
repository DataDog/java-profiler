---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:36:03 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 52-57 cores)</summary>

```
1795001484 57
1795001489 57
1795001494 57
1795001499 57
1795001504 57
1795001509 57
1795001514 57
1795001519 57
1795001524 57
1795001529 57
1795001534 52
1795001539 52
1795001544 52
1795001549 52
1795001554 52
1795001559 52
1795001564 52
1795001569 52
1795001574 52
1795001579 52
```
</details>

---

