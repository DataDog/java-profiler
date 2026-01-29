---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 07:01:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 17.13/sec |
| Health Score | 1071% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 23.77/sec |
| Health Score | 1486% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 70-96 cores)</summary>

```
1769687518 96
1769687523 96
1769687528 96
1769687533 96
1769687538 96
1769687543 96
1769687548 96
1769687553 96
1769687558 92
1769687563 92
1769687568 92
1769687573 92
1769687578 92
1769687583 92
1769687588 92
1769687593 92
1769687598 72
1769687603 72
1769687608 70
1769687613 70
```
</details>

---

