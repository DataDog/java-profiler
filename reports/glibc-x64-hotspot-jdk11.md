---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 60-85 cores)</summary>

```
1795803663 83
1795803668 83
1795803673 83
1795803678 83
1795803683 85
1795803688 85
1795803693 83
1795803698 83
1795803703 83
1795803708 60
1795803713 60
1795803718 60
1795803723 60
1795803728 60
1795803733 60
1795803738 60
1795803743 60
1795803748 60
1795803753 60
1795803758 60
```
</details>

---

