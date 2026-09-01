---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:03:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1788289005 94
1788289010 94
1788289015 94
1788289020 94
1788289025 94
1788289030 92
1788289035 92
1788289040 92
1788289045 90
1788289050 90
1788289055 88
1788289060 88
1788289065 88
1788289070 92
1788289075 92
1788289080 92
1788289085 92
1788289090 92
1788289095 92
1788289100 92
```
</details>

---

