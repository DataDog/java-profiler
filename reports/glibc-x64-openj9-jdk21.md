---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:40:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1790238939 64
1790238944 64
1790238949 64
1790238954 64
1790238959 64
1790238964 64
1790238969 54
1790238974 54
1790238979 54
1790238984 54
1790238989 54
1790238994 54
1790238999 54
1790239004 54
1790239009 54
1790239014 54
1790239019 54
1790239024 54
1790239029 54
1790239034 54
```
</details>

---

