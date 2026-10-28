---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:32:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1793194048 82
1793194053 82
1793194058 82
1793194063 82
1793194068 82
1793194073 82
1793194078 82
1793194083 82
1793194088 82
1793194093 82
1793194098 82
1793194103 82
1793194108 82
1793194113 82
1793194118 82
1793194123 82
1793194128 82
1793194133 82
1793194138 80
1793194143 80
```
</details>

---

