---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:24:34 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 11 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (5 unique values: 77-87 cores)</summary>

```
1794431671 81
1794431676 81
1794431681 81
1794431686 81
1794431691 81
1794431696 81
1794431701 81
1794431706 79
1794431711 79
1794431716 79
1794431721 77
1794431726 77
1794431731 77
1794431736 81
1794431741 81
1794431746 83
1794431751 83
1794431756 83
1794431761 81
1794431766 81
```
</details>

---

