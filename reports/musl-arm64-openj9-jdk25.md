---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 16:14:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 14 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (2 unique values: 36-56 cores)</summary>

```
1786133325 36
1786133330 36
1786133335 36
1786133340 36
1786133345 36
1786133350 36
1786133355 36
1786133360 36
1786133365 36
1786133370 36
1786133375 36
1786133380 56
1786133385 56
1786133390 36
1786133395 36
1786133400 36
1786133405 36
1786133410 36
1786133415 36
1786133420 36
```
</details>

---

