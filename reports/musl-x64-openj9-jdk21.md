---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 11:30:20 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790090710 32
1790090715 32
1790090720 22
1790090725 22
1790090730 22
1790090735 22
1790090740 22
1790090745 22
1790090750 22
1790090755 22
1790090760 22
1790090765 22
1790090770 22
1790090775 22
1790090780 22
1790090785 22
1790090790 22
1790090795 22
1790090800 22
1790090805 22
```
</details>

---

