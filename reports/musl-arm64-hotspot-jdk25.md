---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:31:18 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 11 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1795008323 50
1795008328 50
1795008333 50
1795008338 50
1795008343 52
1795008348 52
1795008353 52
1795008358 52
1795008363 52
1795008368 52
1795008373 52
1795008379 52
1795008384 52
1795008389 52
1795008394 52
1795008399 52
1795008404 52
1795008409 52
1795008414 52
1795008419 52
```
</details>

---

