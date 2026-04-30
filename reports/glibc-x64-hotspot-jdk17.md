---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 09:25:03 EDT

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
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 65-78 cores)</summary>

```
1777555238 78
1777555243 78
1777555248 78
1777555253 78
1777555258 78
1777555263 78
1777555268 76
1777555273 76
1777555278 78
1777555283 78
1777555288 78
1777555293 78
1777555298 78
1777555303 65
1777555308 65
1777555313 65
1777555318 65
1777555323 65
1777555328 65
1777555333 65
```
</details>

---

