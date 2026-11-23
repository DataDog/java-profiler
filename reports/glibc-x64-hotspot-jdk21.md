---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 08:37:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795440788 87
1795440793 87
1795440798 87
1795440803 87
1795440808 87
1795440813 87
1795440818 87
1795440823 85
1795440828 85
1795440833 85
1795440838 85
1795440843 85
1795440848 85
1795440853 85
1795440858 85
1795440863 85
1795440868 85
1795440873 85
1795440878 85
1795440883 85
```
</details>

---

