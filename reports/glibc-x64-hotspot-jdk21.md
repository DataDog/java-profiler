---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 10:07:43 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 905 |
| Sample Rate | 15.08/sec |
| Health Score | 942% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 75-82 cores)</summary>

```
1773237692 82
1773237697 82
1773237702 82
1773237707 82
1773237712 82
1773237717 82
1773237722 82
1773237727 82
1773237732 77
1773237737 77
1773237742 81
1773237747 81
1773237752 81
1773237757 81
1773237762 81
1773237767 81
1773237772 81
1773237777 81
1773237782 78
1773237788 78
```
</details>

---

