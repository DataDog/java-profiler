---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:34:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 14 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790605791 64
1790605796 64
1790605801 64
1790605806 64
1790605811 64
1790605816 64
1790605821 64
1790605826 64
1790605831 64
1790605836 64
1790605841 64
1790605846 64
1790605851 64
1790605856 64
1790605861 64
1790605866 64
1790605871 64
1790605876 64
1790605881 64
1790605886 64
```
</details>

---

