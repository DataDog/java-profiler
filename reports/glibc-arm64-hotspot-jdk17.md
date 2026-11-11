---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:04:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794430784 48
1794430789 48
1794430794 48
1794430799 48
1794430804 48
1794430809 48
1794430814 48
1794430819 48
1794430824 48
1794430829 48
1794430834 48
1794430839 48
1794430844 48
1794430849 48
1794430854 47
1794430859 47
1794430864 47
1794430869 47
1794430874 47
1794430879 47
```
</details>

---

