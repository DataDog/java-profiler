---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 14:44:31 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 14 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (2 unique values: 30-51 cores)</summary>

```
1793734730 30
1793734735 30
1793734740 30
1793734745 30
1793734750 30
1793734755 30
1793734760 30
1793734765 30
1793734770 30
1793734775 30
1793734780 30
1793734785 30
1793734790 30
1793734795 30
1793734800 30
1793734805 30
1793734810 30
1793734815 30
1793734820 30
1793734825 30
```
</details>

---

