---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-11 09:33:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 16-25 cores)</summary>

```
1786454958 16
1786454963 25
1786454968 25
1786454973 25
1786454978 25
1786454983 25
1786454988 23
1786454993 23
1786454998 23
1786455003 23
1786455008 23
1786455013 23
1786455018 23
1786455023 23
1786455028 23
1786455033 23
1786455038 25
1786455043 25
1786455048 25
1786455053 25
```
</details>

---

