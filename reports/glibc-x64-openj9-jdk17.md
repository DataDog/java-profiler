---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:23:09 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795605449 94
1795605454 94
1795605459 94
1795605464 94
1795605469 94
1795605474 94
1795605479 94
1795605484 94
1795605489 96
1795605494 96
1795605499 96
1795605504 96
1795605509 96
1795605514 96
1795605519 96
1795605524 96
1795605529 96
1795605534 96
1795605539 96
1795605544 96
```
</details>

---

