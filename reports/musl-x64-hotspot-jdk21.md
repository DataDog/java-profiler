---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-29 07:38:33 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1777462452 30
1777462457 30
1777462462 30
1777462467 30
1777462472 30
1777462477 30
1777462482 30
1777462487 30
1777462492 30
1777462497 30
1777462502 30
1777462507 30
1777462512 30
1777462517 30
1777462522 30
1777462527 30
1777462532 30
1777462537 32
1777462542 32
1777462547 32
```
</details>

---

