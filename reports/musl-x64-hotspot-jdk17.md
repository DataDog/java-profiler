---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:46:26 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 63-96 cores)</summary>

```
1794393740 93
1794393745 93
1794393750 93
1794393755 96
1794393760 96
1794393765 96
1794393770 96
1794393775 96
1794393780 96
1794393785 96
1794393790 96
1794393795 96
1794393800 96
1794393805 96
1794393810 96
1794393815 96
1794393820 96
1794393825 96
1794393830 96
1794393835 96
```
</details>

---

