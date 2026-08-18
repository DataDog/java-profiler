---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 05:19:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 14 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787044416 48
1787044421 48
1787044426 48
1787044431 48
1787044436 48
1787044441 48
1787044446 48
1787044451 48
1787044456 43
1787044461 43
1787044466 43
1787044472 43
1787044477 43
1787044482 43
1787044487 43
1787044492 43
1787044497 43
1787044502 43
1787044507 43
1787044512 43
```
</details>

---

