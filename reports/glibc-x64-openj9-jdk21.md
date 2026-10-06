---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 08:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 9-26 cores)</summary>

```
1791289494 9
1791289499 9
1791289504 9
1791289509 9
1791289514 9
1791289519 9
1791289524 9
1791289529 9
1791289534 9
1791289539 9
1791289544 9
1791289549 9
1791289554 9
1791289559 9
1791289564 26
1791289569 26
1791289574 26
1791289579 26
1791289584 26
1791289589 26
```
</details>

---

