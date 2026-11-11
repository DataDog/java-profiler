---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:46:23 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 8 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794393770 43
1794393775 43
1794393780 43
1794393785 43
1794393790 43
1794393795 43
1794393800 48
1794393805 48
1794393810 48
1794393815 48
1794393820 48
1794393825 48
1794393830 48
1794393835 48
1794393840 48
1794393845 48
1794393850 48
1794393855 48
1794393860 48
1794393865 48
```
</details>

---

