---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-04 01:00:28 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 13 |
| Allocations | 160 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791089803 48
1791089808 48
1791089813 48
1791089818 48
1791089823 48
1791089828 48
1791089833 48
1791089838 48
1791089843 48
1791089848 48
1791089853 48
1791089858 43
1791089863 43
1791089868 43
1791089873 43
1791089878 43
1791089884 43
1791089889 43
1791089894 43
1791089899 48
```
</details>

---

