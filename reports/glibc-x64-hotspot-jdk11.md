---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 55-64 cores)</summary>

```
1795010729 55
1795010734 55
1795010739 55
1795010744 64
1795010749 64
1795010754 64
1795010759 64
1795010764 64
1795010769 64
1795010774 64
1795010779 64
1795010784 64
1795010789 64
1795010794 64
1795010799 64
1795010804 64
1795010809 64
1795010814 64
1795010819 64
1795010824 64
```
</details>

---

