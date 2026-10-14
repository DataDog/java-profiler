---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-14 10:08:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 11 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1791986609 43
1791986614 43
1791986619 48
1791986624 48
1791986629 48
1791986634 48
1791986639 43
1791986644 43
1791986649 43
1791986655 43
1791986660 43
1791986665 43
1791986670 43
1791986675 43
1791986680 43
1791986685 43
1791986690 43
1791986695 38
1791986700 38
1791986705 38
```
</details>

---

