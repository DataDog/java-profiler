---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 04:47:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 32-37 cores)</summary>

```
1795426917 32
1795426922 32
1795426927 32
1795426932 32
1795426937 32
1795426942 32
1795426947 32
1795426952 32
1795426957 32
1795426962 32
1795426967 32
1795426972 32
1795426977 32
1795426982 32
1795426987 37
1795426992 37
1795426997 37
1795427002 37
1795427007 37
1795427012 37
```
</details>

---

