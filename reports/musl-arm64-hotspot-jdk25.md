---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:21:41 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 11 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1794838606 45
1794838611 45
1794838616 45
1794838621 45
1794838626 45
1794838631 45
1794838636 45
1794838641 45
1794838646 45
1794838651 45
1794838656 45
1794838661 45
1794838666 45
1794838671 45
1794838676 45
1794838681 45
1794838686 45
1794838691 45
1794838696 45
1794838701 45
```
</details>

---

