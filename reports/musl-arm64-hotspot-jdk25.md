---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:36:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (5 unique values: 28-64 cores)</summary>

```
1795001493 59
1795001498 59
1795001503 64
1795001508 64
1795001513 52
1795001518 52
1795001524 52
1795001529 52
1795001534 52
1795001539 52
1795001544 52
1795001549 52
1795001554 52
1795001559 52
1795001564 40
1795001569 40
1795001574 40
1795001579 40
1795001584 28
1795001589 28
```
</details>

---

