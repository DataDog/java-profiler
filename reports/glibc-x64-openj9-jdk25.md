---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 03:32:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 36-96 cores)</summary>

```
1794990520 96
1794990525 96
1794990530 96
1794990535 96
1794990540 96
1794990545 96
1794990550 96
1794990555 96
1794990560 57
1794990565 57
1794990570 57
1794990575 57
1794990580 57
1794990585 57
1794990590 57
1794990595 57
1794990600 57
1794990605 57
1794990610 57
1794990615 57
```
</details>

---

