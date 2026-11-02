---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 06:22:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1793618356 43
1793618361 43
1793618366 43
1793618371 43
1793618376 43
1793618381 43
1793618386 43
1793618391 43
1793618396 43
1793618401 43
1793618406 43
1793618411 43
1793618416 43
1793618421 43
1793618426 43
1793618431 43
1793618436 43
1793618441 43
1793618446 43
1793618451 41
```
</details>

---

