---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:40:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 54-86 cores)</summary>

```
1790238954 63
1790238959 63
1790238964 63
1790238969 63
1790238974 63
1790238979 63
1790238984 86
1790238989 86
1790238994 86
1790238999 86
1790239004 86
1790239009 86
1790239014 86
1790239019 86
1790239024 86
1790239029 86
1790239034 86
1790239039 86
1790239044 86
1790239049 54
```
</details>

---

