---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:51:56 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 926 |
| Sample Rate | 15.43/sec |
| Health Score | 964% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 85-87 cores)</summary>

```
1789677932 87
1789677937 87
1789677942 87
1789677947 87
1789677952 87
1789677957 87
1789677962 87
1789677967 87
1789677972 87
1789677977 87
1789677982 87
1789677987 85
1789677992 85
1789677997 85
1789678002 86
1789678007 86
1789678012 86
1789678017 86
1789678022 86
1789678027 86
```
</details>

---

