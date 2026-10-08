---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:54:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 15 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791470957 48
1791470962 48
1791470967 48
1791470972 48
1791470977 48
1791470982 48
1791470987 48
1791470992 48
1791470997 48
1791471002 48
1791471007 48
1791471012 48
1791471017 48
1791471022 43
1791471027 43
1791471032 43
1791471037 43
1791471042 43
1791471047 43
1791471052 43
```
</details>

---

