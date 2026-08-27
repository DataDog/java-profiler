---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-27 00:56:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 14 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (5 unique values: 53-59 cores)</summary>

```
1787806340 54
1787806345 53
1787806350 53
1787806355 53
1787806360 53
1787806365 53
1787806370 53
1787806375 53
1787806380 54
1787806385 54
1787806390 54
1787806395 54
1787806400 54
1787806406 54
1787806411 54
1787806416 54
1787806421 54
1787806426 59
1787806431 59
1787806436 59
```
</details>

---

