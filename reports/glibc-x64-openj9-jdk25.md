---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 06:31:38 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 79-88 cores)</summary>

```
1794828430 88
1794828435 88
1794828440 88
1794828445 88
1794828450 88
1794828455 88
1794828460 88
1794828465 88
1794828470 88
1794828475 83
1794828480 83
1794828485 83
1794828490 83
1794828495 83
1794828500 83
1794828505 79
1794828510 79
1794828515 79
1794828520 81
1794828525 81
```
</details>

---

