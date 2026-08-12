---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 04:38:14 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1786523564 32
1786523569 32
1786523574 32
1786523579 32
1786523584 32
1786523589 32
1786523594 32
1786523599 32
1786523604 32
1786523609 32
1786523614 32
1786523619 32
1786523624 32
1786523629 20
1786523634 20
1786523639 20
1786523644 20
1786523649 20
1786523654 20
1786523659 20
```
</details>

---

