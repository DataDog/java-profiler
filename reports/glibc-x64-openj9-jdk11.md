---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 05:22:04 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (5 unique values: 78-96 cores)</summary>

```
1787044580 78
1787044585 78
1787044590 80
1787044595 80
1787044600 80
1787044605 80
1787044610 80
1787044615 80
1787044620 80
1787044625 80
1787044630 80
1787044635 80
1787044640 94
1787044645 94
1787044650 94
1787044655 94
1787044660 94
1787044665 94
1787044670 94
1787044675 96
```
</details>

---

