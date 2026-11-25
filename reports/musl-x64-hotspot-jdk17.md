---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:20:52 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 30-56 cores)</summary>

```
1795641372 34
1795641377 34
1795641382 34
1795641387 34
1795641392 34
1795641397 34
1795641402 34
1795641407 34
1795641412 34
1795641417 34
1795641422 34
1795641427 34
1795641432 34
1795641437 34
1795641442 56
1795641447 56
1795641452 56
1795641457 56
1795641462 30
1795641467 30
```
</details>

---

