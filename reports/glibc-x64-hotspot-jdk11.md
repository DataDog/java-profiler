---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:13:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 43-63 cores)</summary>

```
1795529241 46
1795529246 46
1795529251 46
1795529256 46
1795529261 46
1795529266 46
1795529271 46
1795529276 44
1795529281 44
1795529286 44
1795529291 44
1795529296 63
1795529301 63
1795529306 63
1795529311 43
1795529316 43
1795529321 43
1795529326 43
1795529331 43
1795529336 43
```
</details>

---

