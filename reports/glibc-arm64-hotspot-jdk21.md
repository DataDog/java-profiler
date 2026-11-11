---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 04:53:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (4 unique values: 39-64 cores)</summary>

```
1794390650 47
1794390655 47
1794390660 47
1794390665 47
1794390670 47
1794390675 52
1794390680 52
1794390685 64
1794390690 64
1794390695 64
1794390700 47
1794390705 47
1794390710 47
1794390715 47
1794390720 47
1794390725 47
1794390730 47
1794390735 47
1794390740 47
1794390745 47
```
</details>

---

