---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 11:24:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (5 unique values: 70-82 cores)</summary>

```
1778167237 82
1778167242 82
1778167247 77
1778167252 77
1778167257 77
1778167262 77
1778167267 77
1778167272 77
1778167277 79
1778167282 79
1778167288 79
1778167293 79
1778167298 79
1778167303 73
1778167308 73
1778167313 73
1778167318 73
1778167323 73
1778167328 70
1778167333 70
```
</details>

---

