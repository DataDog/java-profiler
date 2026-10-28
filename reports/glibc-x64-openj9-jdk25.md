---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 13:11:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
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
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1793207231 87
1793207236 87
1793207241 87
1793207246 87
1793207251 87
1793207256 87
1793207261 87
1793207266 87
1793207271 87
1793207276 87
1793207281 87
1793207286 87
1793207291 87
1793207296 87
1793207301 87
1793207306 87
1793207311 87
1793207316 85
1793207321 85
1793207326 85
```
</details>

---

