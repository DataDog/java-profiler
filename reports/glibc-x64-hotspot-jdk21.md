---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:56:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 49-70 cores)</summary>

```
1795434744 70
1795434749 70
1795434754 70
1795434759 70
1795434764 70
1795434769 70
1795434774 70
1795434779 70
1795434784 70
1795434789 70
1795434794 70
1795434799 70
1795434804 70
1795434809 49
1795434814 49
1795434819 49
1795434824 49
1795434829 49
1795434834 49
1795434839 49
```
</details>

---

