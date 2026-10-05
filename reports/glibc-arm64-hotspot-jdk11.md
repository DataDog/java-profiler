---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 13:24:30 EDT

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 14 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1791220799 51
1791220804 51
1791220809 51
1791220814 51
1791220819 51
1791220824 51
1791220829 51
1791220834 51
1791220839 51
1791220844 51
1791220849 51
1791220854 51
1791220859 51
1791220864 51
1791220869 51
1791220874 51
1791220879 51
1791220884 51
1791220889 51
1791220894 51
```
</details>

---

