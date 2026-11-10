---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 16:39:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 981 |
| Sample Rate | 16.35/sec |
| Health Score | 1022% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1794346384 64
1794346389 64
1794346394 64
1794346399 59
1794346404 59
1794346409 59
1794346414 59
1794346419 59
1794346424 59
1794346429 59
1794346434 59
1794346439 59
1794346444 59
1794346449 59
1794346454 59
1794346459 59
1794346464 59
1794346469 59
1794346474 64
1794346479 64
```
</details>

---

