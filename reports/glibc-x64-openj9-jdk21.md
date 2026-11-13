---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:48:09 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (6 unique values: 67-84 cores)</summary>

```
1794595276 82
1794595281 82
1794595286 84
1794595291 84
1794595296 84
1794595301 67
1794595306 67
1794595312 67
1794595317 67
1794595322 67
1794595327 67
1794595332 67
1794595337 67
1794595342 69
1794595347 69
1794595352 69
1794595357 69
1794595362 69
1794595367 69
1794595372 69
```
</details>

---

