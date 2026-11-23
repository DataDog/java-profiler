---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:28:07 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1014 |
| Sample Rate | 16.90/sec |
| Health Score | 1056% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 33-38 cores)</summary>

```
1795429417 33
1795429422 33
1795429427 36
1795429432 36
1795429438 36
1795429443 36
1795429448 36
1795429453 36
1795429458 36
1795429463 36
1795429468 36
1795429473 36
1795429478 36
1795429483 36
1795429488 36
1795429493 36
1795429498 36
1795429503 36
1795429508 38
1795429513 38
```
</details>

---

