---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-13 11:55:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1776095503 51
1776095508 51
1776095513 51
1776095518 51
1776095524 51
1776095529 51
1776095534 51
1776095539 51
1776095544 51
1776095549 51
1776095554 51
1776095559 55
1776095564 55
1776095569 59
1776095574 59
1776095579 59
1776095584 59
1776095589 59
1776095594 59
1776095599 59
```
</details>

---

