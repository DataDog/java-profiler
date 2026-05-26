---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-26 09:56:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1779803442 59
1779803447 59
1779803452 59
1779803457 59
1779803462 59
1779803467 59
1779803472 59
1779803477 59
1779803482 59
1779803487 59
1779803492 59
1779803497 59
1779803502 59
1779803507 59
1779803512 56
1779803517 56
1779803522 56
1779803527 56
1779803532 56
1779803537 56
```
</details>

---

