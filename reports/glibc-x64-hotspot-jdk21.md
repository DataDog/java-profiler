---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 08:55:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (6 unique values: 42-55 cores)</summary>

```
1792759891 42
1792759896 42
1792759901 44
1792759906 44
1792759911 55
1792759916 55
1792759921 53
1792759926 53
1792759931 53
1792759936 53
1792759941 48
1792759946 48
1792759951 46
1792759956 46
1792759961 46
1792759966 46
1792759971 46
1792759976 46
1792759981 46
1792759986 46
```
</details>

---

