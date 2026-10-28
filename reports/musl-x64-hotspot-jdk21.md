---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 01:05:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793163615 62
1793163620 62
1793163625 64
1793163630 64
1793163635 64
1793163640 64
1793163645 64
1793163650 64
1793163655 64
1793163660 64
1793163665 64
1793163670 64
1793163675 64
1793163680 64
1793163685 64
1793163690 64
1793163695 64
1793163700 64
1793163705 64
1793163710 64
```
</details>

---

