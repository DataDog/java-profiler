---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 12:33:18 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 29-30 cores)</summary>

```
1791476939 30
1791476944 30
1791476949 30
1791476954 30
1791476959 30
1791476964 30
1791476969 30
1791476974 29
1791476979 29
1791476984 29
1791476989 29
1791476994 29
1791476999 29
1791477004 29
1791477009 29
1791477014 29
1791477019 29
1791477024 29
1791477029 29
1791477034 29
```
</details>

---

