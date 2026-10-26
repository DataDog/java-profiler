---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 08:57:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 71-75 cores)</summary>

```
1793019080 73
1793019085 73
1793019090 73
1793019095 73
1793019100 75
1793019105 75
1793019110 75
1793019115 75
1793019120 73
1793019125 73
1793019130 73
1793019135 73
1793019140 71
1793019145 71
1793019150 71
1793019155 71
1793019160 71
1793019165 71
1793019170 71
1793019175 71
```
</details>

---

