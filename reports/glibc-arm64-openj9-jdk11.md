---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 09:25:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 975 |
| Sample Rate | 16.25/sec |
| Health Score | 1016% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795702840 64
1795702845 64
1795702850 64
1795702855 64
1795702860 64
1795702865 64
1795702870 64
1795702875 64
1795702880 64
1795702885 64
1795702890 64
1795702895 64
1795702900 64
1795702905 64
1795702910 64
1795702915 64
1795702920 64
1795702925 64
1795702930 64
1795702935 64
```
</details>

---

