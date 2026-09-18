---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 12:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 981 |
| Sample Rate | 16.35/sec |
| Health Score | 1022% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 70-73 cores)</summary>

```
1789749354 73
1789749359 73
1789749364 73
1789749369 73
1789749374 73
1789749379 73
1789749384 73
1789749389 73
1789749394 73
1789749399 73
1789749404 73
1789749409 73
1789749414 73
1789749419 71
1789749424 71
1789749429 71
1789749434 71
1789749439 71
1789749444 71
1789749449 71
```
</details>

---

