---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:36:01 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 41-54 cores)</summary>

```
1795001535 41
1795001540 41
1795001545 41
1795001550 41
1795001555 41
1795001560 41
1795001565 41
1795001570 41
1795001575 41
1795001580 41
1795001585 41
1795001590 41
1795001595 54
1795001600 54
1795001605 47
1795001610 47
1795001615 47
1795001620 47
1795001625 47
1795001630 47
```
</details>

---

