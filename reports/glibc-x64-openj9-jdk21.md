---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 04:53:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 72-77 cores)</summary>

```
1794390416 72
1794390421 72
1794390426 72
1794390431 77
1794390436 77
1794390441 77
1794390446 77
1794390451 77
1794390456 77
1794390461 77
1794390466 77
1794390471 77
1794390476 77
1794390481 77
1794390486 77
1794390491 77
1794390496 77
1794390501 77
1794390506 77
1794390511 77
```
</details>

---

