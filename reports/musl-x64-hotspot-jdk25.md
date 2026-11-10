---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 18:14:40 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (4 unique values: 47-83 cores)</summary>

```
1794352212 49
1794352217 49
1794352222 49
1794352227 49
1794352232 49
1794352237 47
1794352242 47
1794352247 47
1794352252 47
1794352257 47
1794352262 47
1794352267 47
1794352272 47
1794352277 47
1794352282 47
1794352287 49
1794352292 49
1794352297 49
1794352302 49
1794352307 49
```
</details>

---

