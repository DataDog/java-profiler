---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:29:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 11 |
| Allocations | 420 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1789737776 60
1789737781 60
1789737786 60
1789737791 60
1789737796 60
1789737801 60
1789737806 64
1789737811 64
1789737816 64
1789737821 64
1789737826 64
1789737831 64
1789737836 64
1789737841 64
1789737846 64
1789737851 64
1789737856 64
1789737861 64
1789737866 64
1789737871 64
```
</details>

---

