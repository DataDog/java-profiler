---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 10:44:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 23-27 cores)</summary>

```
1794411614 27
1794411619 27
1794411624 27
1794411629 27
1794411634 27
1794411639 27
1794411644 27
1794411649 27
1794411654 27
1794411659 27
1794411664 27
1794411669 23
1794411674 23
1794411679 23
1794411684 23
1794411689 23
1794411694 23
1794411699 23
1794411704 23
1794411709 23
```
</details>

---

