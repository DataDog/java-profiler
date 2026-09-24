---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:40:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 42-50 cores)</summary>

```
1790238959 50
1790238964 50
1790238969 50
1790238974 50
1790238979 50
1790238984 50
1790238989 50
1790238994 50
1790238999 50
1790239004 50
1790239009 50
1790239014 50
1790239019 50
1790239024 50
1790239029 50
1790239034 50
1790239039 50
1790239044 50
1790239049 50
1790239054 50
```
</details>

---

