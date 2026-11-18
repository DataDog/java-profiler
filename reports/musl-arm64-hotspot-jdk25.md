---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-18 09:06:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795010490 51
1795010495 51
1795010500 51
1795010505 51
1795010510 51
1795010515 51
1795010520 51
1795010525 46
1795010530 46
1795010535 46
1795010540 46
1795010545 46
1795010550 46
1795010555 46
1795010560 46
1795010566 46
1795010571 46
1795010576 46
1795010581 46
1795010586 46
```
</details>

---

