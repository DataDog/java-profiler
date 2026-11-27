---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 4 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 68-72 cores)</summary>

```
1795803651 72
1795803656 72
1795803661 68
1795803666 68
1795803671 68
1795803676 68
1795803681 68
1795803686 68
1795803691 68
1795803696 68
1795803701 69
1795803706 69
1795803711 69
1795803716 69
1795803721 69
1795803726 69
1795803731 69
1795803736 69
1795803741 69
1795803746 69
```
</details>

---

