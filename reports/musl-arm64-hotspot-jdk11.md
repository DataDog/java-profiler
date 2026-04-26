---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-26 16:34:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1777235385 43
1777235390 43
1777235395 43
1777235400 43
1777235405 43
1777235410 43
1777235415 43
1777235420 43
1777235425 43
1777235430 43
1777235435 43
1777235440 43
1777235445 43
1777235450 43
1777235456 43
1777235461 43
1777235466 43
1777235471 43
1777235476 38
1777235481 38
```
</details>

---

