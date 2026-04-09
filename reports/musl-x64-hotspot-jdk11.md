---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-09 11:18:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (5 unique values: 22-48 cores)</summary>

```
1775747634 22
1775747639 39
1775747644 39
1775747649 41
1775747654 41
1775747659 41
1775747664 41
1775747669 41
1775747674 41
1775747679 41
1775747684 41
1775747689 41
1775747694 41
1775747699 41
1775747704 41
1775747709 44
1775747714 44
1775747719 48
1775747724 48
1775747729 48
```
</details>

---

