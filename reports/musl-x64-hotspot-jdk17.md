---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-08 06:01:09 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (6 unique values: 42-63 cores)</summary>

```
1794135248 46
1794135253 46
1794135258 46
1794135263 46
1794135268 46
1794135273 46
1794135278 46
1794135283 46
1794135288 42
1794135293 42
1794135298 42
1794135303 42
1794135308 42
1794135313 42
1794135318 42
1794135323 42
1794135328 42
1794135333 42
1794135338 42
1794135343 44
```
</details>

---

