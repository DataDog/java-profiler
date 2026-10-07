---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 12:48:08 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791391368 48
1791391373 48
1791391378 48
1791391383 48
1791391388 48
1791391393 48
1791391398 48
1791391403 48
1791391408 48
1791391413 48
1791391418 48
1791391423 48
1791391428 48
1791391433 48
1791391438 43
1791391443 43
1791391448 43
1791391453 43
1791391458 43
1791391463 43
```
</details>

---

