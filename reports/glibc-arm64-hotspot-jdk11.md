---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:38:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 12 |
| Allocations | 179 |

<details>
<summary>CPU Timeline (4 unique values: 41-51 cores)</summary>

```
1795001710 41
1795001715 41
1795001720 41
1795001725 41
1795001730 41
1795001735 46
1795001740 46
1795001745 51
1795001750 51
1795001755 51
1795001760 51
1795001765 51
1795001770 51
1795001775 51
1795001780 51
1795001785 51
1795001790 51
1795001795 51
1795001800 49
1795001805 49
```
</details>

---

