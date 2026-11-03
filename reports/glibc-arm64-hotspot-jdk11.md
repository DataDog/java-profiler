---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 14:44:29 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1793734725 51
1793734730 51
1793734735 51
1793734740 51
1793734745 51
1793734750 51
1793734755 51
1793734760 51
1793734765 51
1793734770 46
1793734775 46
1793734780 46
1793734785 46
1793734790 41
1793734795 41
1793734800 41
1793734805 41
1793734810 41
1793734815 41
1793734820 41
```
</details>

---

