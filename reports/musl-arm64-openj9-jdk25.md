---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:24:15 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 35-64 cores)</summary>

```
1795184334 35
1795184339 35
1795184344 35
1795184349 35
1795184354 35
1795184359 35
1795184364 35
1795184369 35
1795184374 35
1795184379 35
1795184384 35
1795184389 35
1795184394 35
1795184399 50
1795184404 50
1795184409 50
1795184414 50
1795184419 50
1795184424 50
1795184429 50
```
</details>

---

