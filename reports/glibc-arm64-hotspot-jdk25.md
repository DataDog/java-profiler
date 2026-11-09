---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:57:12 EST

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794235959 48
1794235964 48
1794235969 48
1794235974 48
1794235979 48
1794235984 48
1794235989 48
1794235994 48
1794235999 48
1794236004 48
1794236009 48
1794236014 48
1794236019 48
1794236024 48
1794236029 48
1794236034 48
1794236039 48
1794236044 48
1794236049 48
1794236054 48
```
</details>

---

