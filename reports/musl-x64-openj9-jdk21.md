---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:08:51 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (5 unique values: 73-91 cores)</summary>

```
1794931398 73
1794931403 73
1794931408 73
1794931413 73
1794931418 73
1794931423 73
1794931428 78
1794931433 78
1794931438 78
1794931443 78
1794931448 78
1794931453 78
1794931458 78
1794931463 78
1794931468 78
1794931473 80
1794931478 80
1794931483 80
1794931488 80
1794931493 85
```
</details>

---

