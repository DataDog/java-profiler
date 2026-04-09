---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-09 12:09:00 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1775750746 51
1775750751 51
1775750756 51
1775750761 51
1775750766 51
1775750771 51
1775750776 51
1775750781 51
1775750786 51
1775750791 51
1775750796 51
1775750801 48
1775750806 48
1775750811 48
1775750816 48
1775750821 48
1775750826 48
1775750831 48
1775750836 43
1775750841 43
```
</details>

---

