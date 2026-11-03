---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1793734720 32
1793734725 32
1793734730 32
1793734735 32
1793734740 32
1793734745 32
1793734750 32
1793734755 32
1793734760 32
1793734765 32
1793734770 32
1793734775 32
1793734780 32
1793734785 32
1793734790 32
1793734795 32
1793734800 32
1793734805 32
1793734810 32
1793734815 32
```
</details>

---

