---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:29:47 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790093953 48
1790093958 48
1790093963 48
1790093968 48
1790093973 48
1790093978 48
1790093983 48
1790093988 48
1790093993 48
1790093998 48
1790094003 48
1790094008 48
1790094013 48
1790094019 48
1790094024 48
1790094029 48
1790094034 48
1790094039 48
1790094044 48
1790094049 48
```
</details>

---

