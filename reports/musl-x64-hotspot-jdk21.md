---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:23:10 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (3 unique values: 75-84 cores)</summary>

```
1795605453 82
1795605458 82
1795605463 82
1795605468 82
1795605473 82
1795605478 84
1795605483 84
1795605488 84
1795605493 84
1795605498 84
1795605503 84
1795605508 84
1795605513 84
1795605518 84
1795605523 84
1795605528 84
1795605533 84
1795605538 84
1795605543 84
1795605548 84
```
</details>

---

