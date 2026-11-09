---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-09 05:57:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 18-23 cores)</summary>

```
1794221532 18
1794221537 18
1794221542 18
1794221547 18
1794221552 18
1794221557 23
1794221562 23
1794221567 23
1794221572 23
1794221577 23
1794221582 23
1794221587 23
1794221592 23
1794221597 23
1794221602 23
1794221607 23
1794221612 23
1794221617 23
1794221622 23
1794221627 23
```
</details>

---

