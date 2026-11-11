---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:02:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 68-93 cores)</summary>

```
1794405405 69
1794405410 69
1794405415 69
1794405420 69
1794405426 72
1794405431 72
1794405436 74
1794405441 74
1794405446 74
1794405451 74
1794405456 74
1794405461 74
1794405466 74
1794405471 74
1794405476 74
1794405481 74
1794405486 93
1794405491 93
1794405496 93
1794405501 93
```
</details>

---

