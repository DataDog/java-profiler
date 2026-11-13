---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:28:33 EST

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
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 76-82 cores)</summary>

```
1794572468 82
1794572473 82
1794572478 82
1794572483 82
1794572488 82
1794572493 82
1794572498 82
1794572503 82
1794572508 79
1794572513 79
1794572518 81
1794572523 81
1794572528 81
1794572533 78
1794572538 78
1794572543 76
1794572548 76
1794572553 76
1794572558 76
1794572564 76
```
</details>

---

