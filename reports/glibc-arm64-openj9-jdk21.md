---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:47:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 13 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1786527831 32
1786527836 32
1786527841 32
1786527846 32
1786527851 32
1786527856 32
1786527861 32
1786527866 32
1786527871 32
1786527876 32
1786527881 32
1786527886 32
1786527891 32
1786527896 32
1786527901 32
1786527906 32
1786527911 32
1786527916 32
1786527921 32
1786527926 32
```
</details>

---

