---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-11 09:47:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1794408195 71
1794408200 71
1794408205 71
1794408210 71
1794408215 71
1794408221 71
1794408226 71
1794408231 71
1794408236 71
1794408241 71
1794408246 73
1794408251 73
1794408256 73
1794408261 73
1794408266 73
1794408271 73
1794408276 73
1794408281 73
1794408286 73
1794408291 71
```
</details>

---

