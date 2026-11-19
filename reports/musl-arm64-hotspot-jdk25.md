---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:16:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 50-64 cores)</summary>

```
1795108274 64
1795108279 64
1795108284 64
1795108289 64
1795108294 64
1795108299 64
1795108304 64
1795108309 64
1795108314 64
1795108319 64
1795108324 64
1795108329 64
1795108334 64
1795108339 59
1795108344 59
1795108349 59
1795108354 59
1795108359 59
1795108364 59
1795108369 59
```
</details>

---

