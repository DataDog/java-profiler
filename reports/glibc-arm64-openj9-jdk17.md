---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 14 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 26-46 cores)</summary>

```
1795010724 46
1795010729 46
1795010734 46
1795010739 46
1795010744 46
1795010749 46
1795010754 26
1795010759 26
1795010764 26
1795010769 26
1795010774 26
1795010779 26
1795010784 26
1795010789 26
1795010794 26
1795010799 26
1795010804 26
1795010809 26
1795010814 26
1795010819 26
```
</details>

---

