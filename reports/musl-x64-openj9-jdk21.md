---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 10:08:44 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 12 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 84-94 cores)</summary>

```
1786024968 84
1786024973 84
1786024978 88
1786024983 88
1786024988 88
1786024993 88
1786024998 88
1786025003 90
1786025008 90
1786025013 90
1786025018 90
1786025023 90
1786025028 90
1786025033 94
1786025038 94
1786025043 94
1786025048 94
1786025053 94
1786025058 94
1786025063 94
```
</details>

---

