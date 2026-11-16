---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 08:52:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (7 unique values: 84-92 cores)</summary>

```
1794836790 87
1794836795 89
1794836800 89
1794836805 89
1794836810 89
1794836815 89
1794836820 89
1794836825 89
1794836830 89
1794836835 89
1794836840 89
1794836845 89
1794836850 92
1794836855 92
1794836860 90
1794836865 90
1794836870 90
1794836875 90
1794836880 90
1794836885 88
```
</details>

---

