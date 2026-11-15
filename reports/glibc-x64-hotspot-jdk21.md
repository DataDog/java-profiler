---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-15 18:26:28 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (6 unique values: 51-94 cores)</summary>

```
1794784943 51
1794784948 51
1794784953 51
1794784958 51
1794784963 51
1794784968 54
1794784973 54
1794784979 54
1794784984 54
1794784989 54
1794784994 54
1794784999 52
1794785004 52
1794785009 72
1794785014 72
1794785019 72
1794785024 72
1794785029 72
1794785034 72
1794785039 72
```
</details>

---

