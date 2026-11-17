---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 06:32:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 14 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1794914947 38
1794914952 38
1794914957 38
1794914962 38
1794914967 38
1794914972 38
1794914977 38
1794914982 38
1794914987 38
1794914992 33
1794914997 33
1794915002 33
1794915007 33
1794915012 33
1794915017 33
1794915022 33
1794915027 33
1794915032 33
1794915037 33
1794915042 33
```
</details>

---

