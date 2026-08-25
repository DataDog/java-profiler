---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-25 08:39:37 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1787661329 81
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
1787661384 79
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

