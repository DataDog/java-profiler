---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 07:56:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 997 |
| Sample Rate | 16.62/sec |
| Health Score | 1039% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1786103470 76
1786103475 76
1786103480 78
1786103485 78
1786103490 78
1786103495 78
1786103500 78
1786103505 78
1786103510 78
1786103515 78
1786103520 78
1786103525 81
1786103530 81
1786103535 81
1786103540 81
1786103545 81
1786103550 81
1786103555 81
1786103560 81
1786103565 81
```
</details>

---

