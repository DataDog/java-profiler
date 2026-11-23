---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:56:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 73-78 cores)</summary>

```
1795434729 78
1795434734 78
1795434739 78
1795434744 78
1795434749 78
1795434754 78
1795434759 78
1795434764 78
1795434769 78
1795434774 78
1795434779 73
1795434784 73
1795434789 73
1795434794 73
1795434799 73
1795434804 73
1795434809 73
1795434814 73
1795434819 73
1795434824 73
```
</details>

---

