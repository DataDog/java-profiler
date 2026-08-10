---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 09:32:24 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 70-87 cores)</summary>

```
1786368403 79
1786368408 79
1786368413 79
1786368418 79
1786368423 79
1786368428 79
1786368433 79
1786368438 77
1786368443 77
1786368448 77
1786368453 77
1786368458 75
1786368463 75
1786368468 75
1786368473 75
1786368478 75
1786368483 70
1786368488 70
1786368493 70
1786368498 70
```
</details>

---

