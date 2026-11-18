---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 09:10:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 328 |
| Sample Rate | 5.47/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 50-51 cores)</summary>

```
1795010734 51
1795010739 51
1795010744 51
1795010749 50
1795010754 50
1795010759 50
1795010764 50
1795010769 50
1795010774 50
1795010779 50
1795010784 50
1795010789 50
1795010794 50
1795010799 50
1795010804 50
1795010809 51
1795010814 51
1795010819 51
1795010824 51
1795010829 51
```
</details>

---

