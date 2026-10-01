---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 08:26:30 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 36-43 cores)</summary>

```
1790857356 36
1790857361 36
1790857366 36
1790857371 36
1790857376 36
1790857381 36
1790857386 36
1790857391 38
1790857396 38
1790857401 38
1790857406 38
1790857411 38
1790857416 38
1790857421 38
1790857426 38
1790857431 38
1790857436 38
1790857441 43
1790857446 43
1790857451 43
```
</details>

---

