---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:37:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 965 |
| Sample Rate | 16.08/sec |
| Health Score | 1005% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 66-90 cores)</summary>

```
1794396751 69
1794396756 69
1794396761 69
1794396766 69
1794396771 69
1794396776 66
1794396781 66
1794396786 66
1794396791 66
1794396796 66
1794396801 66
1794396806 66
1794396811 66
1794396816 66
1794396821 66
1794396827 66
1794396832 66
1794396837 88
1794396842 88
1794396847 88
```
</details>

---

