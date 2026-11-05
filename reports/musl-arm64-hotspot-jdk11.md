---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:42:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 21-33 cores)</summary>

```
1793882277 21
1793882282 21
1793882287 21
1793882292 21
1793882297 21
1793882302 21
1793882307 21
1793882312 21
1793882317 21
1793882322 21
1793882327 21
1793882332 33
1793882337 33
1793882342 28
1793882347 28
1793882352 28
1793882357 28
1793882362 28
1793882367 28
1793882372 28
```
</details>

---

