---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 78-91 cores)</summary>

```
1795449513 91
1795449518 91
1795449523 91
1795449528 91
1795449533 91
1795449538 89
1795449543 89
1795449548 89
1795449553 89
1795449558 89
1795449563 87
1795449568 87
1795449573 87
1795449578 87
1795449583 87
1795449588 87
1795449593 87
1795449598 87
1795449603 87
1795449608 87
```
</details>

---

