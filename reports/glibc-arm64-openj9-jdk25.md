---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-27 00:56:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1787806342 59
1787806347 59
1787806352 59
1787806357 59
1787806362 59
1787806367 59
1787806372 59
1787806377 59
1787806382 56
1787806387 56
1787806392 56
1787806397 56
1787806402 56
1787806407 56
1787806412 56
1787806417 56
1787806422 56
1787806427 56
1787806432 56
1787806437 56
```
</details>

---

