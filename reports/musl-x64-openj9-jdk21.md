---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 12:07:01 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1794848438 75
1794848443 75
1794848448 75
1794848453 75
1794848458 77
1794848463 77
1794848468 77
1794848473 79
1794848478 79
1794848483 79
1794848488 79
1794848493 79
1794848498 79
1794848503 79
1794848508 79
1794848513 79
1794848518 79
1794848523 79
1794848528 79
1794848533 79
```
</details>

---

