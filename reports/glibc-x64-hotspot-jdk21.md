---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 17:00:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1790110491 48
1790110496 48
1790110501 48
1790110506 48
1790110511 48
1790110516 48
1790110521 48
1790110526 48
1790110531 48
1790110536 48
1790110541 48
1790110546 48
1790110551 48
1790110556 48
1790110561 48
1790110566 48
1790110571 48
1790110576 48
1790110581 48
1790110586 38
```
</details>

---

