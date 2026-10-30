---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 01:04:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1793336389 96
1793336394 96
1793336399 96
1793336404 96
1793336409 96
1793336414 96
1793336419 96
1793336424 96
1793336429 96
1793336434 96
1793336439 96
1793336444 96
1793336449 96
1793336454 88
1793336459 88
1793336464 86
1793336469 86
1793336474 86
1793336479 86
1793336484 86
```
</details>

---

