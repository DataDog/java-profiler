---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-16 07:58:41 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 12 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 73-78 cores)</summary>

```
1776340417 78
1776340422 78
1776340427 78
1776340432 78
1776340437 78
1776340442 78
1776340447 78
1776340452 75
1776340457 75
1776340462 75
1776340467 75
1776340472 75
1776340477 75
1776340482 75
1776340487 75
1776340492 75
1776340497 75
1776340502 75
1776340507 75
1776340512 75
```
</details>

---

