---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:36:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 63-76 cores)</summary>

```
1795001545 76
1795001550 65
1795001555 65
1795001560 65
1795001565 63
1795001570 63
1795001575 63
1795001580 63
1795001585 63
1795001590 63
1795001595 63
1795001600 63
1795001605 63
1795001610 63
1795001615 63
1795001620 63
1795001625 63
1795001630 63
1795001635 63
1795001640 63
```
</details>

---

