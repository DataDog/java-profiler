---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 19:51:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794703630 46
1794703635 46
1794703640 46
1794703645 46
1794703650 48
1794703655 48
1794703660 48
1794703665 48
1794703670 48
1794703675 48
1794703680 48
1794703685 48
1794703690 48
1794703695 48
1794703700 48
1794703705 48
1794703710 48
1794703715 48
1794703720 48
1794703725 48
```
</details>

---

