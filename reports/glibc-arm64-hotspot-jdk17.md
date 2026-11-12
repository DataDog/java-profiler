---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:48:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (4 unique values: 42-46 cores)</summary>

```
1794505459 42
1794505464 43
1794505469 43
1794505474 43
1794505479 43
1794505484 43
1794505489 43
1794505494 43
1794505499 43
1794505504 46
1794505509 46
1794505514 46
1794505519 46
1794505524 46
1794505529 46
1794505534 46
1794505539 46
1794505544 46
1794505549 46
1794505554 46
```
</details>

---

