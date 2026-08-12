---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-12 11:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1786547885 51
1786547890 51
1786547895 51
1786547900 49
1786547905 49
1786547910 49
1786547915 49
1786547920 49
1786547925 49
1786547930 49
1786547935 49
1786547940 49
1786547945 49
1786547950 49
1786547955 49
1786547960 49
1786547965 49
1786547970 49
1786547975 49
1786547980 49
```
</details>

---

