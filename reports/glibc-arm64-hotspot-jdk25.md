---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:08:09 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
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
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795618939 64
1795618944 64
1795618949 64
1795618954 64
1795618959 64
1795618964 64
1795618969 64
1795618974 64
1795618979 64
1795618984 64
1795618989 64
1795618994 64
1795618999 64
1795619004 64
1795619009 64
1795619014 64
1795619019 64
1795619024 64
1795619029 64
1795619034 64
```
</details>

---

