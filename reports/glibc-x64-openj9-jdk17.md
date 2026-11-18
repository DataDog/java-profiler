---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795010754 85
1795010759 85
1795010764 85
1795010769 85
1795010774 85
1795010779 85
1795010784 85
1795010789 85
1795010794 85
1795010799 85
1795010804 85
1795010809 85
1795010814 85
1795010819 85
1795010824 87
1795010829 87
1795010834 87
1795010839 87
1795010844 87
1795010849 87
```
</details>

---

