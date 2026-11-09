---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 10:36:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 93-96 cores)</summary>

```
1794238239 96
1794238245 96
1794238250 96
1794238255 96
1794238260 96
1794238265 96
1794238270 96
1794238275 96
1794238280 96
1794238285 96
1794238290 96
1794238295 96
1794238300 93
1794238305 93
1794238310 93
1794238315 93
1794238320 93
1794238325 93
1794238330 93
1794238335 93
```
</details>

---

