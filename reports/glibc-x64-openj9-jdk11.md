---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 08:29:11 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 992 |
| Sample Rate | 16.53/sec |
| Health Score | 1033% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 58-66 cores)</summary>

```
1791289474 66
1791289479 66
1791289484 66
1791289489 66
1791289494 66
1791289499 66
1791289504 66
1791289509 58
1791289514 58
1791289519 58
1791289524 58
1791289529 58
1791289534 58
1791289539 58
1791289544 58
1791289549 58
1791289554 58
1791289559 58
1791289564 58
1791289569 58
```
</details>

---

