---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 08:29:11 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 30-34 cores)</summary>

```
1791289504 32
1791289509 32
1791289514 32
1791289519 32
1791289524 30
1791289529 30
1791289534 30
1791289539 30
1791289544 30
1791289549 30
1791289554 30
1791289559 30
1791289564 30
1791289569 30
1791289574 34
1791289579 34
1791289584 34
1791289589 34
1791289594 34
1791289599 34
```
</details>

---

