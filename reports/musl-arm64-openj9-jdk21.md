---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 09:56:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 11 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795618308 33
1795618313 33
1795618318 33
1795618323 33
1795618328 33
1795618333 33
1795618338 33
1795618343 33
1795618348 33
1795618353 33
1795618358 33
1795618363 33
1795618368 33
1795618373 33
1795618378 33
1795618383 33
1795618388 33
1795618393 33
1795618398 33
1795618403 64
```
</details>

---

