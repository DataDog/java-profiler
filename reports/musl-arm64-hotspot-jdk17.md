---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:02:29 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (4 unique values: 45-59 cores)</summary>

```
1794405431 46
1794405436 46
1794405441 46
1794405446 46
1794405451 46
1794405456 46
1794405461 46
1794405466 46
1794405471 45
1794405476 45
1794405481 58
1794405486 58
1794405491 58
1794405496 58
1794405501 59
1794405506 59
1794405511 59
1794405516 59
1794405521 59
1794405526 59
```
</details>

---

