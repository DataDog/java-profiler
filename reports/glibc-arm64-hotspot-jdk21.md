---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 05:53:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 9 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795603779 47
1795603784 47
1795603789 47
1795603794 47
1795603799 47
1795603804 47
1795603809 47
1795603814 47
1795603819 64
1795603824 64
1795603829 47
1795603834 47
1795603839 47
1795603844 47
1795603849 47
1795603854 47
1795603859 47
1795603864 47
1795603869 47
1795603874 47
```
</details>

---

