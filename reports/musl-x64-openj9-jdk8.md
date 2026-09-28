---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-28 10:16:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 53-66 cores)</summary>

```
1790604661 66
1790604666 66
1790604671 66
1790604676 66
1790604681 66
1790604686 66
1790604691 66
1790604696 66
1790604701 66
1790604706 66
1790604711 66
1790604716 66
1790604721 66
1790604726 60
1790604731 60
1790604736 60
1790604741 58
1790604746 58
1790604751 58
1790604756 58
```
</details>

---

