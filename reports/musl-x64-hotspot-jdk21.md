---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:10:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794355390 46
1794355395 46
1794355400 46
1794355405 46
1794355410 46
1794355415 46
1794355420 41
1794355425 41
1794355430 41
1794355435 41
1794355440 41
1794355445 41
1794355450 41
1794355455 41
1794355460 46
1794355465 46
1794355470 46
1794355475 46
1794355480 46
1794355485 46
```
</details>

---

