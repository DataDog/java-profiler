---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-06 14:19:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 10 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 12 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1793992443 42
1793992448 42
1793992453 42
1793992458 42
1793992463 42
1793992468 42
1793992473 42
1793992478 48
1793992483 48
1793992488 48
1793992493 48
1793992498 48
1793992503 48
1793992508 48
1793992513 48
1793992518 48
1793992523 48
1793992528 48
1793992533 48
1793992538 48
```
</details>

---

