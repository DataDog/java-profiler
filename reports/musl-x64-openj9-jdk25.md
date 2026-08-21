---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 09:26:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 84-91 cores)</summary>

```
1787318524 86
1787318529 86
1787318534 86
1787318539 86
1787318544 86
1787318549 86
1787318554 86
1787318559 86
1787318564 86
1787318569 86
1787318574 86
1787318579 86
1787318584 86
1787318589 84
1787318594 84
1787318599 84
1787318604 84
1787318609 84
1787318614 84
1787318619 84
```
</details>

---

