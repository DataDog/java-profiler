---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 12:37:05 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 77-85 cores)</summary>

```
1794936758 77
1794936763 77
1794936768 77
1794936773 79
1794936778 79
1794936783 85
1794936788 85
1794936793 85
1794936798 78
1794936803 78
1794936808 78
1794936813 78
1794936818 79
1794936823 79
1794936828 79
1794936833 79
1794936838 79
1794936843 79
1794936848 79
1794936853 79
```
</details>

---

