---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-13 11:55:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1776095484 23
1776095489 23
1776095494 23
1776095499 27
1776095504 27
1776095509 27
1776095514 27
1776095519 27
1776095524 27
1776095529 27
1776095534 48
1776095539 48
1776095544 48
1776095549 48
1776095554 48
1776095559 48
1776095564 48
1776095569 48
1776095574 48
1776095579 48
```
</details>

---

