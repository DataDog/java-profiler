---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 11:54:11 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 10 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 13 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 53-63 cores)</summary>

```
1770137303 63
1770137308 63
1770137313 58
1770137318 58
1770137323 58
1770137328 58
1770137333 53
1770137338 53
1770137343 53
1770137348 53
1770137353 53
1770137358 53
1770137363 53
1770137368 53
1770137373 53
1770137378 53
1770137383 53
1770137388 53
1770137393 53
1770137398 53
```
</details>

---

