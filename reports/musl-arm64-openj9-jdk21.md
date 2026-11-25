---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:20:52 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795641364 64
1795641369 64
1795641374 64
1795641379 64
1795641384 64
1795641389 64
1795641394 64
1795641399 64
1795641404 64
1795641409 64
1795641414 64
1795641419 64
1795641424 64
1795641429 64
1795641434 64
1795641439 64
1795641444 64
1795641449 64
1795641454 64
1795641459 64
```
</details>

---

