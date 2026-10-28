---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:43:22 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1793187453 78
1793187458 78
1793187463 78
1793187468 78
1793187473 78
1793187478 78
1793187483 78
1793187488 78
1793187493 78
1793187498 78
1793187503 76
1793187508 76
1793187513 76
1793187518 76
1793187523 76
1793187528 76
1793187533 76
1793187538 76
1793187543 76
1793187548 76
```
</details>

---

