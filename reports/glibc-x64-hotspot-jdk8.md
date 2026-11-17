---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-17 13:29:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 56-63 cores)</summary>

```
1794939892 56
1794939897 56
1794939902 56
1794939907 56
1794939912 56
1794939917 56
1794939922 59
1794939927 59
1794939932 59
1794939937 59
1794939942 59
1794939947 59
1794939952 59
1794939957 59
1794939962 59
1794939967 59
1794939972 59
1794939977 59
1794939982 61
1794939987 61
```
</details>

---

