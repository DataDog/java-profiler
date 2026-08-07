---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 16:14:07 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 14 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 8-28 cores)</summary>

```
1786133312 28
1786133317 28
1786133322 28
1786133327 28
1786133332 28
1786133337 28
1786133342 28
1786133347 28
1786133352 28
1786133357 28
1786133362 28
1786133367 28
1786133372 28
1786133377 28
1786133382 28
1786133387 28
1786133392 28
1786133397 28
1786133402 28
1786133407 28
```
</details>

---

