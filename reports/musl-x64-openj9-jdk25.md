---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-16 06:24:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 53-60 cores)</summary>

```
1776334539 60
1776334544 60
1776334549 60
1776334554 60
1776334559 60
1776334564 60
1776334569 60
1776334574 60
1776334579 60
1776334584 60
1776334589 60
1776334594 60
1776334599 56
1776334604 56
1776334609 56
1776334614 56
1776334619 53
1776334624 53
1776334629 53
1776334634 53
```
</details>

---

