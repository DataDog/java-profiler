---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-11-11 17:16:30 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 43-46 cores)</summary>

```
1794435185 46
1794435190 46
1794435195 46
1794435200 46
1794435205 46
1794435210 46
1794435215 46
1794435220 46
1794435225 46
1794435230 46
1794435235 46
1794435240 46
1794435245 46
1794435250 46
1794435255 46
1794435260 46
1794435265 46
1794435270 46
1794435275 43
1794435280 43
```
</details>

---

