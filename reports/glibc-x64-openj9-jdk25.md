---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:59:58 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 65-87 cores)</summary>

```
1795431340 87
1795431345 87
1795431350 87
1795431355 87
1795431360 87
1795431365 87
1795431370 87
1795431375 87
1795431380 87
1795431385 87
1795431390 87
1795431395 87
1795431400 87
1795431405 87
1795431410 87
1795431415 78
1795431420 78
1795431425 70
1795431430 70
1795431435 70
```
</details>

---

