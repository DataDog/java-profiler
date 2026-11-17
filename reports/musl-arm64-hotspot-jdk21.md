---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:08:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 28-33 cores)</summary>

```
1794931393 31
1794931398 31
1794931403 31
1794931408 31
1794931413 31
1794931418 33
1794931423 33
1794931428 33
1794931433 33
1794931438 33
1794931443 33
1794931448 33
1794931453 33
1794931458 33
1794931463 33
1794931468 33
1794931473 33
1794931478 33
1794931483 33
1794931488 28
```
</details>

---

