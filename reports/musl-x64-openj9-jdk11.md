---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:28:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (4 unique values: 69-85 cores)</summary>

```
1795627378 69
1795627383 69
1795627388 69
1795627393 69
1795627398 69
1795627403 69
1795627408 69
1795627413 69
1795627418 76
1795627423 76
1795627428 76
1795627433 76
1795627438 85
1795627443 85
1795627448 85
1795627453 75
1795627458 75
1795627463 75
1795627468 75
1795627473 75
```
</details>

---

