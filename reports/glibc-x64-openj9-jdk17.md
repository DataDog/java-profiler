---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 10:59:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 70-78 cores)</summary>

```
1790780068 78
1790780073 78
1790780078 78
1790780083 78
1790780088 75
1790780093 75
1790780098 75
1790780103 75
1790780108 75
1790780113 75
1790780119 75
1790780124 75
1790780129 75
1790780134 75
1790780139 75
1790780144 75
1790780149 73
1790780154 73
1790780159 73
1790780164 76
```
</details>

---

