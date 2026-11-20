---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:41:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795199799 50
1795199804 50
1795199809 50
1795199814 50
1795199819 50
1795199824 50
1795199829 50
1795199834 50
1795199839 50
1795199844 50
1795199849 50
1795199854 50
1795199859 50
1795199864 50
1795199869 50
1795199874 50
1795199879 50
1795199884 50
1795199889 50
1795199894 50
```
</details>

---

