---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 08:42:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 867 |
| Sample Rate | 14.45/sec |
| Health Score | 903% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787661464 94
1787661469 94
1787661474 94
1787661479 94
1787661484 94
1787661489 94
1787661494 96
1787661499 96
1787661504 96
1787661509 96
1787661514 96
1787661519 96
1787661524 96
1787661529 96
1787661534 96
1787661539 96
1787661544 96
1787661549 96
1787661554 96
1787661559 96
```
</details>

---

