---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-03 21:20:30 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
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
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857333 64
1777857338 64
1777857343 64
1777857348 64
1777857353 64
1777857358 64
1777857363 64
1777857368 64
1777857373 64
1777857378 64
1777857383 64
1777857388 64
1777857393 64
1777857398 64
1777857403 64
1777857408 64
1777857413 64
1777857418 64
1777857423 64
1777857428 64
```
</details>

---

