---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:48:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 77-84 cores)</summary>

```
1794325389 84
1794325394 82
1794325399 82
1794325404 82
1794325409 82
1794325414 82
1794325419 82
1794325424 82
1794325429 82
1794325434 82
1794325439 79
1794325444 79
1794325449 79
1794325454 79
1794325459 77
1794325464 77
1794325469 77
1794325474 77
1794325479 77
1794325484 77
```
</details>

---

