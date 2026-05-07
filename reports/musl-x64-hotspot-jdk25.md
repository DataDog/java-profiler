---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:39:49 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 63-84 cores)</summary>

```
1778171730 63
1778171735 63
1778171740 63
1778171745 67
1778171750 67
1778171755 67
1778171760 67
1778171765 67
1778171770 67
1778171775 67
1778171780 67
1778171785 67
1778171790 73
1778171795 73
1778171800 73
1778171805 73
1778171810 73
1778171815 73
1778171820 82
1778171825 82
```
</details>

---

