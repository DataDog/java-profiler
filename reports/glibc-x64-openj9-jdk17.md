---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 09:00:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 57-62 cores)</summary>

```
1778158429 59
1778158434 59
1778158439 59
1778158444 57
1778158449 57
1778158454 57
1778158459 57
1778158464 59
1778158469 59
1778158474 59
1778158479 59
1778158484 59
1778158489 59
1778158494 62
1778158499 62
1778158504 62
1778158509 62
1778158514 62
1778158519 62
1778158524 62
```
</details>

---

