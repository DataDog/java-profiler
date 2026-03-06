---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-06 05:53:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1056 |
| Sample Rate | 17.60/sec |
| Health Score | 1100% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1772794073 27
1772794078 27
1772794083 29
1772794088 29
1772794093 29
1772794098 29
1772794103 29
1772794108 29
1772794113 29
1772794118 29
1772794123 29
1772794128 29
1772794133 29
1772794138 29
1772794143 29
1772794148 29
1772794153 29
1772794158 29
1772794163 29
1772794168 29
```
</details>

---

