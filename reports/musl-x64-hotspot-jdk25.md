---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 05:57:49 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794221517 32
1794221522 32
1794221527 32
1794221532 32
1794221537 32
1794221542 32
1794221547 32
1794221552 32
1794221557 32
1794221562 32
1794221567 32
1794221572 32
1794221577 32
1794221582 32
1794221587 32
1794221592 32
1794221597 32
1794221602 32
1794221607 32
1794221612 30
```
</details>

---

