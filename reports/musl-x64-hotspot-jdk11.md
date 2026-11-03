---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 14:44:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793734725 30
1793734730 30
1793734735 30
1793734740 30
1793734745 30
1793734750 30
1793734755 30
1793734760 30
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
1793734820 32
```
</details>

---

