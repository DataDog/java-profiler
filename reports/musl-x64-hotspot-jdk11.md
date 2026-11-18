---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795010729 85
1795010734 85
1795010739 85
1795010744 85
1795010749 85
1795010754 85
1795010759 85
1795010764 85
1795010769 85
1795010774 85
1795010779 85
1795010784 85
1795010789 85
1795010794 85
1795010799 87
1795010804 87
1795010809 87
1795010814 87
1795010819 87
1795010824 87
```
</details>

---

