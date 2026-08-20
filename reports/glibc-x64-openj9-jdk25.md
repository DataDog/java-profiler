---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-20 12:17:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1787242369 85
1787242374 85
1787242379 85
1787242384 85
1787242389 85
1787242394 85
1787242399 85
1787242404 85
1787242409 85
1787242414 85
1787242419 85
1787242424 85
1787242429 85
1787242434 85
1787242439 85
1787242444 85
1787242449 83
1787242454 83
1787242459 83
1787242464 83
```
</details>

---

