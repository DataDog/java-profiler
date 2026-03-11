---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 08:50:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 11-13 cores)</summary>

```
1773232907 11
1773232912 11
1773232917 11
1773232922 11
1773232927 11
1773232932 11
1773232937 11
1773232942 11
1773232947 11
1773232952 11
1773232957 13
1773232962 13
1773232967 13
1773232972 13
1773232977 13
1773232982 13
1773232987 13
1773232992 13
1773232997 13
1773233002 13
```
</details>

---

