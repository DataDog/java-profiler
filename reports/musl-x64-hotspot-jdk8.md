---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-07 12:24:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 39-41 cores)</summary>

```
1786119564 39
1786119569 39
1786119574 41
1786119579 41
1786119584 41
1786119589 41
1786119594 41
1786119599 41
1786119604 41
1786119609 41
1786119614 41
1786119619 41
1786119624 41
1786119629 41
1786119634 41
1786119639 41
1786119644 41
1786119649 41
1786119654 41
1786119659 41
```
</details>

---

