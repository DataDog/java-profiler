---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 03:21:25 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 55-63 cores)</summary>

```
1791789395 60
1791789400 60
1791789405 60
1791789410 60
1791789415 60
1791789420 60
1791789425 63
1791789430 63
1791789435 63
1791789440 63
1791789445 63
1791789450 63
1791789455 63
1791789460 63
1791789465 63
1791789470 63
1791789475 55
1791789480 55
1791789485 55
1791789490 55
```
</details>

---

