---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 07:01:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 16.40/sec |
| Health Score | 1025% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 24.47/sec |
| Health Score | 1529% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769687533 32
1769687538 32
1769687543 32
1769687548 32
1769687553 32
1769687558 32
1769687563 32
1769687568 32
1769687573 32
1769687578 32
1769687583 32
1769687588 32
1769687593 32
1769687598 32
1769687603 32
1769687608 30
1769687613 30
1769687618 30
1769687623 30
1769687628 30
```
</details>

---

