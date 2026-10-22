---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 13:10:12 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1792688668 80
1792688673 80
1792688678 80
1792688683 82
1792688688 82
1792688693 82
1792688698 82
1792688703 82
1792688708 82
1792688713 82
1792688718 82
1792688723 82
1792688728 82
1792688733 82
1792688738 82
1792688743 82
1792688748 82
1792688753 82
1792688758 82
1792688763 82
```
</details>

---

