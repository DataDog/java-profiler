---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:36:03 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 69-77 cores)</summary>

```
1795001489 69
1795001494 69
1795001499 69
1795001504 69
1795001509 69
1795001514 69
1795001519 69
1795001524 69
1795001529 69
1795001534 69
1795001539 69
1795001544 69
1795001549 77
1795001554 77
1795001559 77
1795001564 77
1795001569 77
1795001574 77
1795001579 77
1795001584 77
```
</details>

---

