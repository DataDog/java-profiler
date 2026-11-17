---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 05:51:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (4 unique values: 44-59 cores)</summary>

```
1794912426 44
1794912431 44
1794912436 49
1794912441 49
1794912446 54
1794912451 54
1794912456 54
1794912461 54
1794912466 54
1794912471 54
1794912476 54
1794912481 54
1794912486 54
1794912491 54
1794912496 54
1794912501 54
1794912506 59
1794912511 59
1794912516 59
1794912521 59
```
</details>

---

