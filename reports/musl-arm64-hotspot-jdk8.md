---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-03 14:44:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1793734695 48
1793734700 48
1793734705 48
1793734710 48
1793734715 48
1793734720 42
1793734725 42
1793734730 42
1793734735 42
1793734740 42
1793734745 42
1793734750 42
1793734755 42
1793734760 42
1793734765 42
1793734770 47
1793734775 47
1793734780 48
1793734785 48
1793734790 48
```
</details>

---

