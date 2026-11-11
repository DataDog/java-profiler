---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:06:32 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 68-93 cores)</summary>

```
1794430784 91
1794430789 91
1794430794 91
1794430799 91
1794430804 91
1794430809 91
1794430814 93
1794430819 93
1794430824 93
1794430829 93
1794430834 93
1794430839 93
1794430844 93
1794430849 93
1794430854 93
1794430859 75
1794430864 75
1794430869 75
1794430874 75
1794430879 75
```
</details>

---

