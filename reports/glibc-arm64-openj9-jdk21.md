---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 05:59:56 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 15 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 16-32 cores)</summary>

```
1790070811 16
1790070816 16
1790070821 16
1790070826 16
1790070831 16
1790070836 32
1790070841 32
1790070846 16
1790070851 16
1790070856 16
1790070861 16
1790070866 16
1790070871 16
1790070876 16
1790070881 16
1790070886 32
1790070891 32
1790070896 16
1790070901 16
1790070906 16
```
</details>

---

