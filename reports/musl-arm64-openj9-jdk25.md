---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 16:39:36 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1794346384 48
1794346389 48
1794346394 48
1794346399 48
1794346404 48
1794346409 48
1794346414 48
1794346419 48
1794346424 48
1794346429 48
1794346434 48
1794346439 48
1794346444 48
1794346449 48
1794346454 48
1794346459 48
1794346464 45
1794346469 45
1794346474 45
1794346479 45
```
</details>

---

