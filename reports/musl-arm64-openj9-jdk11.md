---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:36:50 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794497409 46
1794497414 46
1794497419 46
1794497424 46
1794497429 46
1794497434 51
1794497439 51
1794497444 51
1794497449 51
1794497454 51
1794497459 51
1794497464 51
1794497469 51
1794497474 51
1794497479 51
1794497484 51
1794497489 51
1794497494 51
1794497499 51
1794497504 51
```
</details>

---

