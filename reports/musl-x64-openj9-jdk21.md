---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 01:03:55 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1791867574 75
1791867579 75
1791867584 75
1791867589 75
1791867594 75
1791867599 77
1791867604 77
1791867609 77
1791867614 77
1791867619 77
1791867624 77
1791867629 79
1791867634 79
1791867639 79
1791867644 79
1791867649 79
1791867654 79
1791867659 79
1791867664 79
1791867669 79
```
</details>

---

