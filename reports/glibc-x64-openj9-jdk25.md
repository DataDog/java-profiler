---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 05:19:53 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1787044366 96
1787044371 96
1787044376 96
1787044381 96
1787044386 96
1787044391 96
1787044396 80
1787044401 80
1787044406 80
1787044411 80
1787044416 78
1787044421 78
1787044426 78
1787044431 78
1787044436 78
1787044441 78
1787044446 78
1787044451 78
1787044456 78
1787044461 78
```
</details>

---

