---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 16:40:59 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 51-96 cores)</summary>

```
1792787789 96
1792787794 75
1792787799 75
1792787804 75
1792787809 75
1792787814 75
1792787819 75
1792787824 75
1792787829 75
1792787834 75
1792787839 75
1792787844 51
1792787849 51
1792787854 51
1792787859 51
1792787864 51
1792787869 51
1792787874 51
1792787879 51
1792787884 51
```
</details>

---

