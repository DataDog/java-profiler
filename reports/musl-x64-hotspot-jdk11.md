---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:58:22 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 50-78 cores)</summary>

```
1795452824 50
1795452829 59
1795452834 59
1795452839 58
1795452844 58
1795452849 58
1795452854 58
1795452859 58
1795452864 58
1795452869 58
1795452874 58
1795452879 58
1795452884 58
1795452889 58
1795452894 58
1795452899 58
1795452904 58
1795452909 58
1795452914 58
1795452919 58
```
</details>

---

