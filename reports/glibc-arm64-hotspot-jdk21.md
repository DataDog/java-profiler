---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-28 12:57:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1787935974 48
1787935979 48
1787935984 48
1787935989 48
1787935994 48
1787935999 47
1787936004 47
1787936009 47
1787936014 47
1787936019 47
1787936024 47
1787936029 47
1787936034 47
1787936039 47
1787936044 47
1787936049 47
1787936054 48
1787936059 48
1787936064 48
1787936069 48
```
</details>

---

