---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 01:13:27 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 89-94 cores)</summary>

```
1792645553 89
1792645558 89
1792645563 89
1792645568 89
1792645573 89
1792645578 89
1792645583 89
1792645588 89
1792645593 89
1792645598 89
1792645603 89
1792645608 89
1792645613 89
1792645618 89
1792645623 89
1792645628 94
1792645633 94
1792645638 94
1792645643 94
1792645648 89
```
</details>

---

