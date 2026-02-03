---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 08:38:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 933 |
| Sample Rate | 15.55/sec |
| Health Score | 972% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1770125481 28
1770125486 28
1770125491 28
1770125496 32
1770125501 32
1770125506 32
1770125511 32
1770125516 32
1770125521 32
1770125526 32
1770125531 32
1770125536 30
1770125541 30
1770125546 30
1770125551 30
1770125556 30
1770125561 30
1770125566 30
1770125571 30
1770125576 30
```
</details>

---

