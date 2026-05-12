---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:45:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 68-73 cores)</summary>

```
1778582446 68
1778582451 68
1778582456 68
1778582461 68
1778582466 68
1778582471 68
1778582476 68
1778582481 68
1778582486 68
1778582491 73
1778582496 73
1778582501 73
1778582506 73
1778582511 73
1778582516 73
1778582521 73
1778582526 73
1778582531 73
1778582536 73
1778582541 73
```
</details>

---

