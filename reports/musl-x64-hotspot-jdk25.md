---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-17 11:08:51 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 82-92 cores)</summary>

```
1794931390 82
1794931395 82
1794931400 82
1794931405 92
1794931410 92
1794931415 92
1794931420 90
1794931425 90
1794931430 90
1794931435 90
1794931440 90
1794931445 90
1794931450 90
1794931455 90
1794931460 90
1794931465 90
1794931470 90
1794931475 90
1794931480 90
1794931485 90
```
</details>

---

