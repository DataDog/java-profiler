---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-15 09:57:54 EDT

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
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 76-82 cores)</summary>

```
1792072288 82
1792072293 80
1792072298 80
1792072303 80
1792072308 80
1792072313 80
1792072318 80
1792072323 80
1792072328 80
1792072333 80
1792072338 80
1792072343 80
1792072348 80
1792072353 80
1792072358 80
1792072363 80
1792072368 80
1792072373 76
1792072378 76
1792072383 76
```
</details>

---

