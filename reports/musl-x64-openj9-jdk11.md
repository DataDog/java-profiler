---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:47:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (4 unique values: 76-82 cores)</summary>

```
1795426914 80
1795426919 80
1795426924 82
1795426929 82
1795426934 82
1795426939 82
1795426944 82
1795426949 82
1795426954 82
1795426959 82
1795426964 82
1795426969 82
1795426974 82
1795426979 80
1795426984 80
1795426989 78
1795426994 78
1795426999 78
1795427004 78
1795427009 78
```
</details>

---

