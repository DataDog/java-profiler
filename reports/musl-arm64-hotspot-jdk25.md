---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 19:15:10 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793142523 48
1793142528 48
1793142533 48
1793142538 48
1793142543 48
1793142548 48
1793142553 48
1793142558 48
1793142563 48
1793142568 48
1793142573 48
1793142578 48
1793142583 48
1793142588 48
1793142593 48
1793142598 48
1793142603 48
1793142608 48
1793142613 48
1793142618 48
```
</details>

---

