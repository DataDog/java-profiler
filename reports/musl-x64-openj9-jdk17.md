---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 04:18:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 71-81 cores)</summary>

```
1786522369 73
1786522374 73
1786522379 73
1786522384 73
1786522389 73
1786522394 73
1786522399 73
1786522404 73
1786522409 73
1786522414 73
1786522419 71
1786522424 71
1786522429 71
1786522434 71
1786522439 71
1786522444 71
1786522449 74
1786522454 74
1786522459 76
1786522464 76
```
</details>

---

