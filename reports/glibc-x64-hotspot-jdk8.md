---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 51-68 cores)</summary>

```
1795803663 58
1795803668 58
1795803673 58
1795803678 58
1795803683 58
1795803688 58
1795803693 58
1795803698 58
1795803703 58
1795803708 58
1795803713 58
1795803718 58
1795803723 66
1795803728 66
1795803733 68
1795803738 68
1795803743 68
1795803748 68
1795803753 51
1795803758 51
```
</details>

---

