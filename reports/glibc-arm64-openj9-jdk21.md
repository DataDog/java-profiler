---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 04:30:57 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795166833 50
1795166838 50
1795166843 50
1795166848 50
1795166853 50
1795166858 50
1795166863 50
1795166868 50
1795166873 50
1795166878 50
1795166883 50
1795166888 50
1795166893 50
1795166898 50
1795166903 50
1795166908 50
1795166913 50
1795166918 50
1795166923 50
1795166928 50
```
</details>

---

