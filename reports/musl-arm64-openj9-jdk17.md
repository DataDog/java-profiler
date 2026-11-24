---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:47:32 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 12 |
| Allocations | 95 |

<details>
<summary>CPU Timeline (2 unique values: 20-25 cores)</summary>

```
1795531338 20
1795531344 20
1795531349 20
1795531354 20
1795531359 20
1795531364 20
1795531369 20
1795531374 20
1795531379 20
1795531384 25
1795531389 25
1795531394 20
1795531399 20
1795531404 20
1795531409 20
1795531414 20
1795531419 20
1795531424 20
1795531429 20
1795531434 20
```
</details>

---

