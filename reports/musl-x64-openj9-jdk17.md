---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 10:31:19 EDT

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
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (5 unique values: 80-90 cores)</summary>

```
1790346362 88
1790346367 88
1790346372 88
1790346377 88
1790346382 88
1790346387 88
1790346392 90
1790346397 90
1790346402 80
1790346407 80
1790346412 80
1790346417 80
1790346422 80
1790346427 84
1790346432 84
1790346437 86
1790346442 86
1790346447 86
1790346452 86
1790346457 86
```
</details>

---

