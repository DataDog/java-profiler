---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:46:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 903 |
| Sample Rate | 15.05/sec |
| Health Score | 941% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 77-80 cores)</summary>

```
1786376358 78
1786376363 78
1786376368 78
1786376373 80
1786376378 80
1786376383 77
1786376388 77
1786376393 77
1786376398 77
1786376403 77
1786376408 77
1786376413 77
1786376418 77
1786376423 77
1786376428 77
1786376433 77
1786376438 77
1786376443 77
1786376448 77
1786376453 77
```
</details>

---

