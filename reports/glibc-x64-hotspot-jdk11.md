---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 08:50:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 18-30 cores)</summary>

```
1773232917 30
1773232922 30
1773232927 30
1773232932 20
1773232937 20
1773232942 20
1773232947 20
1773232952 18
1773232957 18
1773232962 18
1773232967 18
1773232972 18
1773232977 18
1773232982 18
1773232987 18
1773232992 18
1773232997 18
1773233002 18
1773233007 18
1773233012 18
```
</details>

---

