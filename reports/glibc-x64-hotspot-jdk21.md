---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:39:29 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 32-55 cores)</summary>

```
1790238939 41
1790238944 41
1790238949 41
1790238954 41
1790238959 41
1790238964 41
1790238969 41
1790238974 41
1790238979 41
1790238984 32
1790238989 32
1790238994 32
1790238999 32
1790239004 32
1790239009 32
1790239014 32
1790239019 32
1790239024 32
1790239029 32
1790239034 55
```
</details>

---

