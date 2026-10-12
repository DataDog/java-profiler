---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 05:09:12 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 7 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 5 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791795901 43
1791795906 43
1791795911 48
1791795916 48
1791795921 43
1791795926 43
1791795931 43
1791795936 43
1791795941 43
1791795946 43
1791795951 43
1791795956 43
1791795961 43
1791795966 43
1791795971 48
1791795976 48
1791795981 48
1791795986 48
1791795991 48
1791795996 48
```
</details>

---

