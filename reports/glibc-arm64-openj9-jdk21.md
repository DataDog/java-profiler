---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 06:31:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 42-51 cores)</summary>

```
1794828488 42
1794828493 42
1794828498 42
1794828503 42
1794828508 42
1794828513 42
1794828518 42
1794828523 42
1794828528 42
1794828533 42
1794828538 44
1794828543 44
1794828548 44
1794828553 44
1794828558 46
1794828563 46
1794828568 46
1794828573 46
1794828578 51
1794828583 51
```
</details>

---

