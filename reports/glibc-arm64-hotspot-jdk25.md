---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-19 09:29:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795098374 50
1795098379 50
1795098384 50
1795098389 50
1795098394 50
1795098399 50
1795098404 50
1795098409 50
1795098414 50
1795098419 50
1795098424 50
1795098429 50
1795098434 50
1795098439 50
1795098444 50
1795098449 50
1795098454 50
1795098459 50
1795098464 50
1795098469 50
```
</details>

---

