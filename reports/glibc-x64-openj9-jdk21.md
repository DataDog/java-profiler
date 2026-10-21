---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 09:26:04 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (5 unique values: 66-81 cores)</summary>

```
1792588870 68
1792588875 68
1792588880 68
1792588885 68
1792588890 66
1792588895 66
1792588900 66
1792588905 66
1792588910 66
1792588915 66
1792588920 66
1792588925 66
1792588930 81
1792588935 81
1792588940 81
1792588945 81
1792588950 81
1792588955 76
1792588960 76
1792588965 76
```
</details>

---

