---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-16 05:46:46 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1786873400 79
1786873405 79
1786873410 79
1786873415 81
1786873420 81
1786873425 81
1786873430 81
1786873435 81
1786873440 81
1786873445 81
1786873450 81
1786873455 81
1786873460 81
1786873465 81
1786873470 81
1786873475 81
1786873480 81
1786873485 81
1786873490 81
1786873495 81
```
</details>

---

