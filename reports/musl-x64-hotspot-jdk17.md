---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 20:36:48 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794360726 30
1794360731 30
1794360736 30
1794360741 32
1794360746 32
1794360751 30
1794360756 30
1794360761 30
1794360766 30
1794360771 30
1794360776 30
1794360781 30
1794360786 30
1794360791 30
1794360796 30
1794360801 30
1794360806 30
1794360811 30
1794360816 30
1794360821 30
```
</details>

---

