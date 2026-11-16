---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:06:59 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 87-90 cores)</summary>

```
1794848444 90
1794848449 90
1794848454 90
1794848459 90
1794848464 90
1794848469 90
1794848474 87
1794848479 87
1794848484 87
1794848489 89
1794848494 89
1794848499 89
1794848504 89
1794848509 89
1794848514 89
1794848519 89
1794848524 89
1794848529 89
1794848534 89
1794848539 89
```
</details>

---

