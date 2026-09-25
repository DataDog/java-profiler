---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 10:31:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790346424 50
1790346429 50
1790346434 50
1790346439 50
1790346444 50
1790346449 50
1790346455 50
1790346460 50
1790346465 50
1790346470 50
1790346475 50
1790346480 50
1790346485 50
1790346490 50
1790346495 50
1790346500 50
1790346505 50
1790346510 50
1790346515 50
1790346520 50
```
</details>

---

