---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-15 09:27:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 12 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 29-33 cores)</summary>

```
1792070624 29
1792070629 29
1792070634 29
1792070639 29
1792070644 29
1792070649 29
1792070654 29
1792070659 29
1792070664 29
1792070669 29
1792070674 29
1792070679 29
1792070684 29
1792070689 29
1792070694 29
1792070699 29
1792070704 29
1792070709 29
1792070714 29
1792070719 29
```
</details>

---

