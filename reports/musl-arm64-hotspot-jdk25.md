---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:02:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 11 |
| Allocations | 110 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 45-59 cores)</summary>

```
1794405414 46
1794405419 46
1794405424 46
1794405429 46
1794405434 46
1794405439 46
1794405444 46
1794405449 46
1794405454 46
1794405459 46
1794405464 46
1794405469 45
1794405474 45
1794405479 58
1794405484 58
1794405489 58
1794405494 58
1794405499 59
1794405504 59
1794405509 59
```
</details>

---

