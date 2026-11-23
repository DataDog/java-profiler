---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 08:37:37 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 49-56 cores)</summary>

```
1795440745 56
1795440750 56
1795440755 56
1795440760 56
1795440765 56
1795440770 56
1795440775 56
1795440780 56
1795440785 56
1795440790 56
1795440795 56
1795440800 54
1795440805 54
1795440810 54
1795440815 54
1795440820 54
1795440825 49
1795440830 49
1795440835 49
1795440840 49
```
</details>

---

