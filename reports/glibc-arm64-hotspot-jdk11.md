---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:53:29 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 4 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 52-64 cores)</summary>

```
1778582834 57
1778582839 57
1778582844 57
1778582849 57
1778582854 57
1778582859 64
1778582864 64
1778582869 64
1778582874 64
1778582879 64
1778582884 64
1778582889 64
1778582894 64
1778582899 64
1778582904 64
1778582909 64
1778582914 64
1778582919 64
1778582924 64
1778582929 64
```
</details>

---

