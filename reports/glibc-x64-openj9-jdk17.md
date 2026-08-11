---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 09:28:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 12 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 53-68 cores)</summary>

```
1786454480 68
1786454485 68
1786454490 68
1786454495 68
1786454500 68
1786454505 68
1786454510 68
1786454515 68
1786454520 68
1786454525 68
1786454530 68
1786454535 68
1786454540 68
1786454545 68
1786454550 68
1786454555 68
1786454560 68
1786454565 68
1786454570 68
1786454575 53
```
</details>

---

