---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:45:28 EST

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
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 89-94 cores)</summary>

```
1794497532 94
1794497537 94
1794497542 94
1794497547 94
1794497552 94
1794497557 89
1794497562 89
1794497567 89
1794497572 89
1794497577 89
1794497582 89
1794497587 89
1794497592 91
1794497597 91
1794497602 91
1794497607 91
1794497612 91
1794497617 91
1794497622 91
1794497627 91
```
</details>

---

