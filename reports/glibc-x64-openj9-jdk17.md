---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-24 05:38:26 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 39-46 cores)</summary>

```
1792834330 46
1792834335 46
1792834340 46
1792834345 46
1792834350 46
1792834355 44
1792834360 44
1792834365 44
1792834370 44
1792834375 46
1792834380 46
1792834385 46
1792834390 46
1792834395 46
1792834400 46
1792834405 44
1792834410 44
1792834415 44
1792834420 44
1792834425 44
```
</details>

---

