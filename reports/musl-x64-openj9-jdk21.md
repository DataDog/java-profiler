---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 04:13:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 21-32 cores)</summary>

```
1791965374 21
1791965379 21
1791965384 21
1791965389 21
1791965394 21
1791965399 23
1791965404 23
1791965409 23
1791965414 23
1791965419 23
1791965424 23
1791965429 23
1791965434 23
1791965439 23
1791965444 23
1791965449 32
1791965454 32
1791965459 25
1791965464 25
1791965469 25
```
</details>

---

