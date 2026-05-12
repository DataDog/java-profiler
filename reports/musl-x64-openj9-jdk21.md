---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 06:46:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1048 |
| Sample Rate | 17.47/sec |
| Health Score | 1092% |
| Threads | 12 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 74-86 cores)</summary>

```
1778582406 82
1778582411 86
1778582416 86
1778582421 86
1778582426 86
1778582431 86
1778582436 86
1778582441 86
1778582446 86
1778582451 86
1778582456 86
1778582461 86
1778582466 86
1778582471 86
1778582476 86
1778582481 86
1778582486 86
1778582491 86
1778582496 86
1778582501 86
```
</details>

---

