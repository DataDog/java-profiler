---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-27 00:56:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (4 unique values: 20-26 cores)</summary>

```
1787806359 26
1787806364 26
1787806369 26
1787806374 26
1787806379 22
1787806384 22
1787806389 22
1787806394 22
1787806399 22
1787806404 22
1787806409 22
1787806414 22
1787806419 22
1787806424 22
1787806429 22
1787806434 22
1787806439 21
1787806444 21
1787806449 20
1787806454 20
```
</details>

---

