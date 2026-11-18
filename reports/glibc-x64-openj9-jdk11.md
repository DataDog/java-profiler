---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:30:23 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 41-44 cores)</summary>

```
1794997515 42
1794997520 42
1794997525 42
1794997530 42
1794997535 42
1794997540 42
1794997545 42
1794997550 42
1794997555 42
1794997560 44
1794997565 44
1794997570 44
1794997575 44
1794997580 41
1794997585 41
1794997590 41
1794997595 41
1794997600 41
1794997605 41
1794997610 41
```
</details>

---

