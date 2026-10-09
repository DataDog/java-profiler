---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 06:38:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1791541860 46
1791541865 46
1791541870 46
1791541875 46
1791541880 46
1791541885 46
1791541890 46
1791541895 46
1791541900 46
1791541905 46
1791541910 46
1791541915 46
1791541920 46
1791541925 46
1791541930 46
1791541935 51
1791541940 51
1791541945 51
1791541950 51
1791541955 51
```
</details>

---

