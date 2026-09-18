---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:50:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 942 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1789738896 31
1789738901 31
1789738906 33
1789738911 33
1789738916 33
1789738921 33
1789738926 33
1789738931 33
1789738936 33
1789738941 33
1789738946 33
1789738951 33
1789738956 33
1789738961 33
1789738966 33
1789738971 33
1789738976 33
1789738981 33
1789738986 33
1789738991 33
```
</details>

---

