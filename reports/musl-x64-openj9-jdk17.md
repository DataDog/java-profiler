---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:57:03 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1794509523 27
1794509528 29
1794509533 29
1794509538 29
1794509543 27
1794509548 27
1794509553 27
1794509558 27
1794509563 27
1794509568 27
1794509573 29
1794509578 29
1794509583 29
1794509588 29
1794509593 29
1794509598 29
1794509603 32
1794509608 32
1794509613 32
1794509618 32
```
</details>

---

