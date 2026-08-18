---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 05:22:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1787044543 43
1787044548 43
1787044553 43
1787044558 48
1787044563 48
1787044568 39
1787044573 39
1787044578 39
1787044583 39
1787044588 39
1787044593 39
1787044598 39
1787044603 39
1787044608 39
1787044613 39
1787044618 39
1787044623 39
1787044628 39
1787044633 39
1787044638 39
```
</details>

---

