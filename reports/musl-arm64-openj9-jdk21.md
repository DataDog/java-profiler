---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:44:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 36-51 cores)</summary>

```
1794588043 51
1794588048 51
1794588053 51
1794588058 51
1794588063 51
1794588068 51
1794588073 46
1794588078 46
1794588083 41
1794588088 41
1794588093 41
1794588098 41
1794588103 41
1794588108 41
1794588113 41
1794588118 41
1794588123 41
1794588128 36
1794588133 36
1794588138 36
```
</details>

---

