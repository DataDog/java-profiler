---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:33:00 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794497242 48
1794497247 48
1794497252 48
1794497257 48
1794497262 48
1794497267 48
1794497272 48
1794497277 48
1794497282 48
1794497287 47
1794497292 47
1794497297 47
1794497302 47
1794497307 47
1794497312 47
1794497317 47
1794497322 47
1794497327 47
1794497332 47
1794497337 47
```
</details>

---

