---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 05:53:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 12 |
| Allocations | 90 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 14 |
| Allocations | 190 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791884930 46
1791884935 46
1791884940 46
1791884945 46
1791884950 46
1791884955 46
1791884960 46
1791884965 51
1791884970 51
1791884975 51
1791884980 51
1791884985 51
1791884990 51
1791884995 51
1791885000 51
1791885005 51
1791885010 51
1791885015 51
1791885020 51
1791885025 51
```
</details>

---

