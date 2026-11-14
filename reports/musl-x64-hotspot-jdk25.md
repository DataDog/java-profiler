---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-14 13:57:45 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 75-96 cores)</summary>

```
1794682387 77
1794682392 77
1794682397 77
1794682402 77
1794682407 77
1794682412 77
1794682417 77
1794682422 77
1794682427 77
1794682432 77
1794682437 77
1794682442 75
1794682447 75
1794682452 94
1794682457 94
1794682462 94
1794682467 96
1794682472 96
1794682477 96
1794682482 96
```
</details>

---

