---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 13:58:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 78-82 cores)</summary>

```
1793123650 78
1793123655 78
1793123660 78
1793123665 78
1793123670 78
1793123675 78
1793123680 78
1793123685 82
1793123690 82
1793123695 82
1793123700 82
1793123705 82
1793123710 82
1793123715 82
1793123720 82
1793123725 82
1793123730 82
1793123735 82
1793123740 82
1793123745 82
```
</details>

---

