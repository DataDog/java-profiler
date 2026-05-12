---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:46:27 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 12 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778582411 59
1778582416 59
1778582421 59
1778582426 59
1778582431 59
1778582436 59
1778582441 59
1778582446 64
1778582451 64
1778582456 64
1778582461 64
1778582466 64
1778582471 64
1778582476 64
1778582481 64
1778582486 64
1778582491 64
1778582496 64
1778582501 64
1778582506 64
```
</details>

---

