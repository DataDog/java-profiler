---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:36:02 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795001510 62
1795001515 62
1795001520 62
1795001525 62
1795001530 62
1795001535 62
1795001540 62
1795001545 62
1795001550 62
1795001555 62
1795001560 62
1795001565 64
1795001570 64
1795001575 62
1795001580 62
1795001585 62
1795001590 62
1795001595 62
1795001600 62
1795001605 62
```
</details>

---

