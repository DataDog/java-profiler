---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 06:19:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 14 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795518922 34
1795518927 34
1795518932 34
1795518937 34
1795518942 34
1795518947 34
1795518952 34
1795518957 34
1795518962 34
1795518967 34
1795518972 34
1795518977 34
1795518982 34
1795518987 29
1795518992 29
1795518997 29
1795519002 29
1795519007 29
1795519012 29
1795519017 29
```
</details>

---

