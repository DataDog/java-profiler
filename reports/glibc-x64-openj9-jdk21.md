---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 08:01:28 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1790596579 96
1790596584 96
1790596589 96
1790596594 96
1790596599 96
1790596604 96
1790596609 96
1790596614 96
1790596619 96
1790596624 91
1790596629 91
1790596634 91
1790596639 91
1790596644 91
1790596649 91
1790596654 89
1790596659 89
1790596664 89
1790596669 89
1790596674 89
```
</details>

---

