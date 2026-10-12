---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 03:21:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 17-34 cores)</summary>

```
1791789405 34
1791789410 34
1791789415 34
1791789420 34
1791789425 22
1791789430 22
1791789435 22
1791789440 22
1791789445 22
1791789450 22
1791789455 22
1791789460 22
1791789465 22
1791789470 22
1791789475 22
1791789480 22
1791789485 17
1791789490 17
1791789495 17
1791789500 17
```
</details>

---

