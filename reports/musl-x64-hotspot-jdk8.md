---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-06 15:13:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 52-57 cores)</summary>

```
1793995705 57
1793995710 57
1793995715 57
1793995720 57
1793995725 52
1793995730 52
1793995735 52
1793995740 54
1793995745 54
1793995750 54
1793995755 54
1793995760 54
1793995765 54
1793995770 54
1793995775 54
1793995780 54
1793995785 54
1793995790 54
1793995795 54
1793995800 54
```
</details>

---

