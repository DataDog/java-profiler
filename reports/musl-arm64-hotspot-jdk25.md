---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 05:51:52 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1794912426 33
1794912431 33
1794912436 33
1794912441 33
1794912446 33
1794912451 33
1794912456 33
1794912461 33
1794912466 33
1794912471 33
1794912476 33
1794912481 33
1794912486 33
1794912491 33
1794912496 33
1794912501 33
1794912506 33
1794912511 33
1794912516 38
1794912521 38
```
</details>

---

