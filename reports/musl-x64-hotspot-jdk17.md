---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-10 17:36:43 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 55-65 cores)</summary>

```
1770762506 65
1770762511 65
1770762516 65
1770762521 65
1770762526 65
1770762531 65
1770762536 65
1770762541 65
1770762546 65
1770762551 65
1770762556 65
1770762561 65
1770762566 65
1770762571 59
1770762576 59
1770762581 59
1770762586 59
1770762591 55
1770762596 55
1770762601 55
```
</details>

---

