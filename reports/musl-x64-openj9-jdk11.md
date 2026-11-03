---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 14:44:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 54-66 cores)</summary>

```
1793734699 66
1793734704 66
1793734709 66
1793734714 66
1793734719 66
1793734725 66
1793734730 66
1793734735 66
1793734740 66
1793734745 66
1793734750 66
1793734755 66
1793734760 58
1793734765 58
1793734770 54
1793734775 54
1793734780 54
1793734785 54
1793734790 54
1793734795 54
```
</details>

---

