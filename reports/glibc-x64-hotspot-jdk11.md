---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-14 10:14:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 8 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 58-93 cores)</summary>

```
1786716538 59
1786716543 59
1786716548 59
1786716553 59
1786716558 61
1786716563 61
1786716568 61
1786716573 61
1786716578 61
1786716583 61
1786716588 61
1786716593 61
1786716598 61
1786716603 61
1786716608 58
1786716613 58
1786716618 58
1786716623 58
1786716628 58
1786716633 58
```
</details>

---

