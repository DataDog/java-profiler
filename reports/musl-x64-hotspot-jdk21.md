---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 08:39:37 EDT

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
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1787661329 79
1787661334 79
1787661339 79
1787661344 79
1787661349 79
1787661354 79
1787661359 79
1787661364 79
1787661369 79
1787661374 81
1787661379 81
1787661384 81
1787661389 79
1787661394 79
1787661399 79
1787661404 79
1787661409 79
1787661414 79
1787661419 81
1787661424 81
```
</details>

---

