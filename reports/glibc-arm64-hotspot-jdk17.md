---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 08:18:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 232 |
| Sample Rate | 3.87/sec |
| Health Score | 242% |
| Threads | 12 |
| Allocations | 103 |

<details>
<summary>CPU Timeline (5 unique values: 40-46 cores)</summary>

```
1793362354 40
1793362359 45
1793362364 45
1793362369 45
1793362374 45
1793362379 45
1793362384 45
1793362389 44
1793362394 44
1793362399 44
1793362404 44
1793362409 44
1793362414 44
1793362419 44
1793362424 44
1793362429 44
1793362434 44
1793362439 44
1793362444 44
1793362449 43
```
</details>

---

