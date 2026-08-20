---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 06:18:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1787220871 48
1787220876 48
1787220881 48
1787220886 48
1787220891 48
1787220897 48
1787220902 48
1787220907 48
1787220912 48
1787220917 48
1787220922 48
1787220927 48
1787220932 47
1787220937 47
1787220942 47
1787220947 47
1787220952 47
1787220957 47
1787220962 47
1787220967 47
```
</details>

---

