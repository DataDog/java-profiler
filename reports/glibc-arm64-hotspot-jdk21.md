---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 10:24:26 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 10 |
| Allocations | 118 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1790864415 51
1790864420 51
1790864425 51
1790864430 51
1790864435 51
1790864440 51
1790864445 46
1790864450 46
1790864455 46
1790864460 46
1790864465 46
1790864470 46
1790864475 46
1790864480 46
1790864485 46
1790864490 46
1790864495 46
1790864500 46
1790864505 46
1790864510 46
```
</details>

---

