---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 06:42:06 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1792492599 15
1792492604 15
1792492609 15
1792492614 15
1792492619 15
1792492624 15
1792492629 15
1792492634 15
1792492639 15
1792492644 15
1792492649 15
1792492654 32
1792492659 32
1792492664 32
1792492669 32
1792492674 32
1792492679 32
1792492684 32
1792492689 32
1792492694 32
```
</details>

---

