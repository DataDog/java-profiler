---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 63-71 cores)</summary>

```
1793995715 71
1793995720 71
1793995725 71
1793995730 71
1793995735 66
1793995740 66
1793995745 63
1793995750 63
1793995755 63
1793995760 63
1793995765 63
1793995770 63
1793995775 63
1793995780 63
1793995785 63
1793995790 63
1793995795 63
1793995800 63
1793995805 63
1793995810 63
```
</details>

---

