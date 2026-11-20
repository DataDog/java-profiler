---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 04:30:56 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 30-50 cores)</summary>

```
1795166813 50
1795166818 50
1795166823 50
1795166828 50
1795166833 50
1795166838 50
1795166843 50
1795166848 50
1795166853 50
1795166858 50
1795166863 30
1795166868 30
1795166873 30
1795166878 30
1795166883 30
1795166888 30
1795166893 30
1795166898 30
1795166903 30
1795166908 30
```
</details>

---

