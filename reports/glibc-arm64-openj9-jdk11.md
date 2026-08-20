---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 09:32:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787232435 48
1787232440 48
1787232445 48
1787232450 43
1787232455 43
1787232460 43
1787232465 43
1787232470 43
1787232475 43
1787232480 43
1787232485 43
1787232490 43
1787232495 43
1787232500 48
1787232505 48
1787232510 48
1787232515 48
1787232520 48
1787232525 48
1787232530 48
```
</details>

---

