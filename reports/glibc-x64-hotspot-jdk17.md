---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:06:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 61-86 cores)</summary>

```
1795010482 61
1795010487 61
1795010492 61
1795010497 61
1795010502 61
1795010507 61
1795010512 61
1795010517 61
1795010522 66
1795010527 66
1795010532 69
1795010537 69
1795010542 69
1795010547 69
1795010552 69
1795010557 69
1795010562 86
1795010567 86
1795010572 86
1795010577 86
```
</details>

---

