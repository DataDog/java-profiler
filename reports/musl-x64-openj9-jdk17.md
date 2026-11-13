---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 53-60 cores)</summary>

```
1794567575 53
1794567580 53
1794567585 55
1794567590 55
1794567595 55
1794567600 55
1794567605 60
1794567610 60
1794567615 60
1794567620 60
1794567625 60
1794567630 60
1794567635 60
1794567641 60
1794567646 60
1794567651 60
1794567656 60
1794567661 60
1794567666 60
1794567671 60
```
</details>

---

