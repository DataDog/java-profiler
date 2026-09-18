---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:26:48 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1789737796 66
1789737801 66
1789737806 66
1789737811 64
1789737816 64
1789737821 64
1789737826 64
1789737831 64
1789737836 64
1789737841 64
1789737846 64
1789737851 64
1789737856 62
1789737861 62
1789737866 62
1789737871 62
1789737876 64
1789737881 64
1789737886 64
1789737891 64
```
</details>

---

