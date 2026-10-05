---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 03:35:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
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
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1127 |
| Sample Rate | 18.78/sec |
| Health Score | 1174% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791185440 46
1791185445 46
1791185450 51
1791185455 51
1791185460 51
1791185465 51
1791185470 51
1791185475 51
1791185480 51
1791185485 51
1791185490 51
1791185495 51
1791185500 51
1791185505 51
1791185510 51
1791185515 51
1791185520 51
1791185525 51
1791185530 51
1791185535 51
```
</details>

---

