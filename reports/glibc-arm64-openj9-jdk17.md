---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 08:29:10 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 14 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 31-48 cores)</summary>

```
1791289499 31
1791289504 31
1791289509 31
1791289514 31
1791289519 31
1791289524 31
1791289529 31
1791289534 31
1791289539 31
1791289544 31
1791289549 31
1791289554 31
1791289559 31
1791289564 31
1791289569 31
1791289574 31
1791289579 31
1791289584 36
1791289589 36
1791289594 36
```
</details>

---

