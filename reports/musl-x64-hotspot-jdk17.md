---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:04:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 80-85 cores)</summary>

```
1794430779 82
1794430784 80
1794430789 80
1794430794 80
1794430799 80
1794430804 80
1794430809 80
1794430814 80
1794430819 80
1794430824 80
1794430829 83
1794430834 83
1794430839 83
1794430844 83
1794430849 83
1794430854 83
1794430859 83
1794430864 83
1794430869 83
1794430874 83
```
</details>

---

