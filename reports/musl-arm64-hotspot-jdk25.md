---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:20:13 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 12 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1790853333 38
1790853338 38
1790853343 38
1790853348 38
1790853353 40
1790853358 40
1790853363 40
1790853368 40
1790853373 40
1790853378 40
1790853383 40
1790853388 40
1790853393 40
1790853398 40
1790853403 40
1790853408 40
1790853413 40
1790853418 43
1790853423 43
1790853428 43
```
</details>

---

