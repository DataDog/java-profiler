---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 14:19:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 62-72 cores)</summary>

```
1793992404 72
1793992409 72
1793992414 72
1793992419 72
1793992424 72
1793992429 72
1793992434 72
1793992439 72
1793992444 72
1793992449 62
1793992454 62
1793992459 62
1793992464 62
1793992469 62
1793992474 62
1793992479 62
1793992484 62
1793992489 62
1793992494 62
1793992499 62
```
</details>

---

