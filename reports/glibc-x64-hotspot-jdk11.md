---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:22:57 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 57-74 cores)</summary>

```
1793830760 57
1793830765 57
1793830770 74
1793830775 74
1793830780 74
1793830786 74
1793830791 74
1793830796 74
1793830801 74
1793830806 74
1793830811 74
1793830816 74
1793830821 74
1793830826 74
1793830831 70
1793830836 70
1793830841 70
1793830846 70
1793830851 72
1793830856 72
```
</details>

---

