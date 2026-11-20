---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:56:26 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 9 |
| Allocations | 115 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (4 unique values: 39-45 cores)</summary>

```
1795186305 39
1795186310 39
1795186315 45
1795186320 45
1795186325 42
1795186330 42
1795186335 42
1795186340 42
1795186345 42
1795186350 42
1795186355 42
1795186360 42
1795186365 42
1795186370 42
1795186375 42
1795186380 45
1795186385 45
1795186390 45
1795186395 45
1795186400 43
```
</details>

---

