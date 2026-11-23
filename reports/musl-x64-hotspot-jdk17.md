---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:59:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 75-82 cores)</summary>

```
1795452884 78
1795452889 78
1795452894 78
1795452899 78
1795452905 78
1795452910 75
1795452915 75
1795452920 75
1795452925 75
1795452930 75
1795452935 75
1795452940 75
1795452945 75
1795452950 75
1795452955 75
1795452960 75
1795452965 75
1795452970 75
1795452975 82
1795452980 82
```
</details>

---

