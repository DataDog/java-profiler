---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 12:24:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 13 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794244808 51
1794244813 46
1794244818 46
1794244824 46
1794244829 46
1794244834 46
1794244839 46
1794244844 46
1794244849 46
1794244854 46
1794244859 46
1794244864 46
1794244869 46
1794244874 46
1794244879 46
1794244884 51
1794244889 51
1794244894 51
1794244899 51
1794244904 51
```
</details>

---

