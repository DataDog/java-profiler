---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:05:36 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 70-89 cores)</summary>

```
1793739688 70
1793739693 70
1793739698 70
1793739703 70
1793739708 70
1793739713 89
1793739718 89
1793739723 87
1793739728 87
1793739733 87
1793739738 87
1793739743 87
1793739748 89
1793739753 89
1793739758 89
1793739763 89
1793739768 88
1793739773 88
1793739778 88
1793739783 88
```
</details>

---

