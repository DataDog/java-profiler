---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 12:17:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 91-96 cores)</summary>

```
1787242364 96
1787242369 96
1787242374 96
1787242379 96
1787242384 91
1787242389 91
1787242394 91
1787242399 91
1787242404 91
1787242409 91
1787242414 91
1787242419 91
1787242424 91
1787242429 91
1787242434 91
1787242439 91
1787242444 91
1787242449 91
1787242454 91
1787242459 91
```
</details>

---

