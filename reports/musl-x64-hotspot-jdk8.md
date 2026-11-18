---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:36:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 53-73 cores)</summary>

```
1795001484 71
1795001489 71
1795001494 71
1795001499 71
1795001504 71
1795001509 71
1795001514 71
1795001519 71
1795001524 71
1795001529 71
1795001534 71
1795001539 73
1795001544 73
1795001549 53
1795001554 53
1795001559 53
1795001564 53
1795001569 53
1795001574 53
1795001579 53
```
</details>

---

