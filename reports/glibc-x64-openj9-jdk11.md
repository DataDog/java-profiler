---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 12:43:40 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 19.57/sec |
| Health Score | 1223% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 23.00/sec |
| Health Score | 1438% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 53-72 cores)</summary>

```
1769708269 53
1769708274 53
1769708280 53
1769708285 53
1769708290 53
1769708295 53
1769708300 68
1769708305 68
1769708310 68
1769708315 68
1769708320 68
1769708325 72
1769708330 72
1769708335 72
1769708340 72
1769708345 72
1769708350 72
1769708355 72
1769708360 72
1769708365 72
```
</details>

---

