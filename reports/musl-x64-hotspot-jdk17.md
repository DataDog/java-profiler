---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 06:16:41 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1792145498 12
1792145503 12
1792145508 12
1792145513 12
1792145518 12
1792145523 12
1792145528 12
1792145533 32
1792145538 32
1792145543 32
1792145548 32
1792145553 32
1792145558 32
1792145563 32
1792145568 32
1792145573 32
1792145578 32
1792145583 32
1792145588 32
1792145593 32
```
</details>

---

