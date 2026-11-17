---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 05:58:59 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (4 unique values: 61-81 cores)</summary>

```
1794912838 62
1794912843 62
1794912848 62
1794912853 62
1794912858 64
1794912863 64
1794912868 64
1794912873 64
1794912878 64
1794912883 64
1794912888 64
1794912893 64
1794912898 64
1794912903 64
1794912909 64
1794912914 64
1794912919 64
1794912924 64
1794912929 64
1794912934 81
```
</details>

---

