---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 10:44:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 898 |
| Sample Rate | 14.97/sec |
| Health Score | 936% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 35-47 cores)</summary>

```
1794411572 35
1794411577 35
1794411582 47
1794411587 47
1794411592 47
1794411597 47
1794411602 47
1794411607 47
1794411612 47
1794411617 47
1794411622 47
1794411627 47
1794411632 47
1794411637 47
1794411642 47
1794411647 47
1794411652 47
1794411657 47
1794411662 47
1794411667 47
```
</details>

---

