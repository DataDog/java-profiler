---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:25:58 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1793722735 11
1793722740 11
1793722745 11
1793722750 11
1793722755 11
1793722760 11
1793722765 11
1793722770 11
1793722775 11
1793722780 11
1793722785 11
1793722790 32
1793722795 32
1793722800 32
1793722805 32
1793722810 32
1793722815 32
1793722820 30
1793722825 30
1793722830 30
```
</details>

---

