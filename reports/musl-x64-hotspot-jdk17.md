---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-03 21:20:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1049 |
| Sample Rate | 17.48/sec |
| Health Score | 1092% |
| Threads | 11 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (2 unique values: 93-96 cores)</summary>

```
1777857328 93
1777857333 93
1777857338 93
1777857343 93
1777857348 96
1777857353 96
1777857358 96
1777857363 96
1777857368 96
1777857373 96
1777857378 96
1777857383 96
1777857388 96
1777857393 96
1777857398 96
1777857404 96
1777857409 96
1777857414 96
1777857419 96
1777857424 96
```
</details>

---

