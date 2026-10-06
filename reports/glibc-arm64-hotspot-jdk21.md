---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 11:23:36 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791299969 43
1791299974 43
1791299979 48
1791299984 48
1791299989 48
1791299994 48
1791299999 48
1791300004 48
1791300009 48
1791300014 48
1791300019 48
1791300024 48
1791300029 48
1791300034 48
1791300039 48
1791300044 48
1791300049 48
1791300054 48
1791300059 48
1791300064 48
```
</details>

---

