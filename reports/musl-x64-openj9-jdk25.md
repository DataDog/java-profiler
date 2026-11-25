---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:34:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 87-91 cores)</summary>

```
1795613393 87
1795613398 87
1795613403 87
1795613408 87
1795613413 87
1795613418 87
1795613423 87
1795613428 87
1795613433 87
1795613438 87
1795613443 87
1795613448 87
1795613453 91
1795613458 91
1795613463 91
1795613468 91
1795613473 91
1795613478 91
1795613483 91
1795613488 91
```
</details>

---

