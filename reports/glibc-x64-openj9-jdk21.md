---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 08:26:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 10 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 76-80 cores)</summary>

```
1794489706 76
1794489711 78
1794489716 78
1794489721 78
1794489726 78
1794489731 78
1794489736 80
1794489741 80
1794489746 80
1794489751 80
1794489756 80
1794489761 80
1794489766 80
1794489771 80
1794489776 80
1794489781 80
1794489786 80
1794489791 80
1794489796 80
1794489801 80
```
</details>

---

