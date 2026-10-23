---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 10:56:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 77-86 cores)</summary>

```
1792767095 79
1792767100 79
1792767105 79
1792767110 81
1792767115 81
1792767120 81
1792767125 81
1792767130 81
1792767135 81
1792767140 81
1792767145 83
1792767150 83
1792767155 79
1792767160 79
1792767165 79
1792767170 77
1792767175 77
1792767180 77
1792767185 77
1792767190 81
```
</details>

---

