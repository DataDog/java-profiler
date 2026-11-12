---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 05:00:23 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1794477264 59
1794477269 59
1794477274 61
1794477279 61
1794477284 61
1794477289 61
1794477294 61
1794477299 61
1794477304 61
1794477309 61
1794477314 61
1794477319 61
1794477324 61
1794477329 61
1794477334 61
1794477339 61
1794477344 61
1794477349 61
1794477354 61
1794477359 61
```
</details>

---

