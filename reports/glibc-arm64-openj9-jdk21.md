---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-27 00:56:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 11 |
| Allocations | 193 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (5 unique values: 53-59 cores)</summary>

```
1787806364 53
1787806369 53
1787806374 53
1787806379 54
1787806384 54
1787806389 54
1787806394 54
1787806399 54
1787806404 54
1787806409 54
1787806414 54
1787806419 54
1787806424 59
1787806429 59
1787806434 59
1787806439 59
1787806444 58
1787806449 58
1787806454 58
1787806459 57
```
</details>

---

