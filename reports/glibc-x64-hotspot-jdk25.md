---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 05:27:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 10 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1794306125 53
1794306130 53
1794306135 53
1794306140 53
1794306145 51
1794306150 51
1794306155 51
1794306160 51
1794306165 51
1794306170 51
1794306175 51
1794306180 51
1794306185 51
1794306190 51
1794306195 51
1794306200 51
1794306205 51
1794306210 51
1794306215 51
1794306220 51
```
</details>

---

