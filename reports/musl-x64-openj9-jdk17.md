---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 07:47:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 80-88 cores)</summary>

```
1794487356 88
1794487361 88
1794487366 88
1794487371 88
1794487376 86
1794487381 86
1794487386 86
1794487391 86
1794487396 86
1794487401 86
1794487406 86
1794487411 86
1794487416 86
1794487421 86
1794487426 82
1794487431 82
1794487436 82
1794487441 82
1794487446 82
1794487451 80
```
</details>

---

