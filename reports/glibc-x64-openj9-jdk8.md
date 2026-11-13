---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 10:44:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 76-86 cores)</summary>

```
1794584402 86
1794584407 86
1794584412 86
1794584417 86
1794584422 86
1794584427 86
1794584432 80
1794584437 80
1794584442 80
1794584447 80
1794584452 80
1794584457 80
1794584462 80
1794584467 80
1794584472 80
1794584477 80
1794584482 80
1794584487 78
1794584492 78
1794584497 76
```
</details>

---

