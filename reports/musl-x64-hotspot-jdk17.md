---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:10:49 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 34-53 cores)</summary>

```
1795010735 36
1795010740 34
1795010745 34
1795010750 34
1795010755 34
1795010760 36
1795010765 36
1795010770 36
1795010775 36
1795010780 36
1795010785 53
1795010790 53
1795010795 51
1795010800 51
1795010805 51
1795010810 51
1795010815 51
1795010820 51
1795010825 51
1795010830 51
```
</details>

---

