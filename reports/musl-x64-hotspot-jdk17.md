---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 06:37:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1787740366 49
1787740371 49
1787740376 49
1787740381 49
1787740386 49
1787740391 51
1787740396 51
1787740401 51
1787740406 51
1787740411 51
1787740416 51
1787740421 51
1787740426 51
1787740431 51
1787740436 49
1787740441 49
1787740446 49
1787740451 49
1787740456 49
1787740461 49
```
</details>

---

