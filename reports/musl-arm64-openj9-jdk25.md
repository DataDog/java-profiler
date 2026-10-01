---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 08:26:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 10 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1790857346 36
1790857351 36
1790857356 36
1790857361 36
1790857366 36
1790857371 36
1790857376 36
1790857381 36
1790857386 36
1790857391 36
1790857396 36
1790857401 36
1790857406 36
1790857411 36
1790857416 36
1790857421 36
1790857426 36
1790857431 36
1790857436 36
1790857441 36
```
</details>

---

