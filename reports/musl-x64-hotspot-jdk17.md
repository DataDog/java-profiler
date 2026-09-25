---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 10:31:18 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 68-72 cores)</summary>

```
1790346467 68
1790346472 68
1790346477 68
1790346482 68
1790346487 68
1790346492 68
1790346497 68
1790346502 68
1790346507 68
1790346512 68
1790346517 68
1790346522 68
1790346527 68
1790346533 70
1790346538 70
1790346543 70
1790346548 70
1790346553 72
1790346558 72
1790346563 72
```
</details>

---

