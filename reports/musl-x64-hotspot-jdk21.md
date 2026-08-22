---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-21 20:15:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787357482 79
1787357487 79
1787357492 81
1787357497 81
1787357502 81
1787357507 81
1787357512 81
1787357517 81
1787357522 81
1787357527 81
1787357532 81
1787357537 81
1787357542 81
1787357547 81
1787357552 81
1787357557 81
1787357562 81
1787357567 81
1787357572 81
1787357577 81
```
</details>

---

