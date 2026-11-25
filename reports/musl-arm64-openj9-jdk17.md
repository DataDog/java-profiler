---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 05:36:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 15 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795602637 33
1795602642 33
1795602647 33
1795602652 33
1795602657 33
1795602662 33
1795602667 64
1795602672 64
1795602677 64
1795602682 64
1795602687 64
1795602692 64
1795602697 64
1795602702 64
1795602707 64
1795602712 64
1795602717 64
1795602722 64
1795602727 64
1795602732 64
```
</details>

---

