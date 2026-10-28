---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:14:07 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1793185451 45
1793185456 45
1793185461 45
1793185466 45
1793185471 45
1793185476 45
1793185481 45
1793185486 46
1793185491 46
1793185496 46
1793185501 46
1793185506 46
1793185511 46
1793185516 46
1793185521 46
1793185526 46
1793185531 46
1793185536 46
1793185541 46
1793185546 46
```
</details>

---

