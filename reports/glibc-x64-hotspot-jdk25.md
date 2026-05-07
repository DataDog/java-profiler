---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 06:49:54 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 71-92 cores)</summary>

```
1778150757 71
1778150762 71
1778150767 71
1778150772 88
1778150777 88
1778150782 88
1778150787 88
1778150792 90
1778150797 90
1778150802 92
1778150807 92
1778150812 92
1778150817 92
1778150822 92
1778150827 92
1778150832 92
1778150837 92
1778150842 92
1778150847 92
1778150852 92
```
</details>

---

