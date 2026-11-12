---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 08:26:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 73-79 cores)</summary>

```
1794489686 79
1794489691 77
1794489696 77
1794489701 77
1794489706 77
1794489711 77
1794489716 77
1794489721 77
1794489726 77
1794489731 75
1794489736 75
1794489741 75
1794489746 75
1794489751 75
1794489756 75
1794489761 75
1794489766 75
1794489771 75
1794489776 75
1794489781 75
```
</details>

---

