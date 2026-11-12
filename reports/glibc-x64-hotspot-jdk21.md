---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 08:02:20 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
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
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794488238 32
1794488243 32
1794488248 32
1794488253 32
1794488258 32
1794488263 32
1794488268 32
1794488273 32
1794488278 32
1794488283 32
1794488288 32
1794488293 32
1794488298 32
1794488304 32
1794488309 32
1794488314 32
1794488319 32
1794488324 32
1794488329 32
1794488334 32
```
</details>

---

