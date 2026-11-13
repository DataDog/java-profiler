---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 14:19:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 11 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1794597302 51
1794597307 51
1794597312 51
1794597317 51
1794597322 51
1794597327 51
1794597332 46
1794597337 46
1794597342 41
1794597347 41
1794597352 41
1794597357 41
1794597362 41
1794597367 41
1794597372 41
1794597377 41
1794597382 41
1794597387 41
1794597392 41
1794597397 41
```
</details>

---

