---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:02:28 EST

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
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 12 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794405419 48
1794405424 48
1794405429 48
1794405434 43
1794405439 43
1794405444 43
1794405449 43
1794405454 43
1794405459 43
1794405464 43
1794405469 43
1794405474 43
1794405479 43
1794405484 43
1794405489 43
1794405494 43
1794405499 43
1794405504 48
1794405509 48
1794405514 48
```
</details>

---

