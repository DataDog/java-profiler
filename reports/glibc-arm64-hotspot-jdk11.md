---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 09:09:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1794319440 48
1794319445 48
1794319450 46
1794319455 46
1794319460 46
1794319465 46
1794319470 46
1794319475 46
1794319480 46
1794319485 46
1794319490 43
1794319495 43
1794319500 43
1794319505 43
1794319510 43
1794319515 43
1794319520 43
1794319525 45
1794319530 45
1794319535 45
```
</details>

---

